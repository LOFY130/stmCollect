#include "frame.h"
static const quint32 MAGIC = 0xAABBCCDD;
static const int HDR_LEN = 16;
static const quint8  FRAME_SIG   = 0x5A;
static const quint32 FRAME_TAG32 = 0x20260206;
Frame::Frame(QObject *parent) : QObject(parent)
{

}
//解析帧
void Frame::feed(const QByteArray &data)
{
    buf += data;

    while (true) {
        // 如果缓冲区小于帧头长度，则等待下一次数据
        if (buf.size() < HDR_LEN) return;

        // 找到下一个 MAGIC 字节的位置
        int pos = -1;
        for (int i = 0; i <= buf.size() - 4; ++i) {
            const uchar *p = (const uchar*)buf.constData() + i;
            if (rd_u32_le(p) == MAGIC) { pos = i; break; }
        }

        // 如果没有找到 MAGIC，则丢弃前面的无效数据并返回
        if (pos < 0) {
            if (buf.size() > 3) {
                buf = buf.right(3);  // 保留最后3字节，防止跨帧
            }
            return;
        }

        // 丢掉 MAGIC 前的无效数据
        if (pos > 0) buf.remove(0, pos);

        // 如果数据不足以组成完整的帧头，则等待更多数据
        if (buf.size() < HDR_LEN) return;

        // 解析帧头
        const uchar *h = (const uchar*)buf.constData();
        quint16 seq = rd_u16_le(h + 4);
        quint8 type = h[6];
        quint16 payloadLen = rd_u16_le(h + 8);
        quint16 sampleCount = rd_u16_le(h + 10);
        quint8  sig  = h[7];
        quint32 tag  = rd_u32_le(h + 12);

        if (sig != FRAME_SIG || tag != FRAME_TAG32) {
            emit parseError("SIG/TAG不匹配，丢弃一个magic重新同步");
            buf.remove(0, 4);
            continue;
        }
        // 校验帧头，确保帧的大小合理
        if (sampleCount == 0 || sampleCount > 2048) {
            emit parseError("sampleCount非法，丢弃一个magic重新同步");
            buf.remove(0, 4);  // 丢弃这一帧并继续同步
            continue;
        }

        if (payloadLen != sampleCount * 2) {
            emit parseError("payloadLen != sampleCount*2，丢弃一个magic重新同步");
            buf.remove(0, 4);  // 丢弃这一帧并继续同步
            continue;
        }

        int frameLen = HDR_LEN + payloadLen;
        if (buf.size() < frameLen) return;  // 如果数据不足一帧，等待下一次数据

        // 提取样本数据
        QVector<quint16> samples;
        samples.resize(sampleCount);
        const uchar *p = (const uchar*)buf.constData() + HDR_LEN;
        for (int i = 0; i < sampleCount; ++i) {
            samples[i] = (quint16)p[0] | ((quint16)p[1] << 8);
            p += 2;
        }

        // 检查样本值并记录坏点
        QVector<int> badIdx;
        badIdx.reserve(16);
        quint16 maxv = 0;

        for (int i = 0; i < samples.size(); ++i) {
            if (samples[i] > maxv) maxv = samples[i];
            if (samples[i] > 4095) badIdx.push_back(i);
        }

        if (!badIdx.isEmpty()) {
            emit parseError(QString("BAD FRAME: seq=%1 type=%2 bad=%3 max=%4")
                            .arg(seq).arg(type).arg(badIdx.size()).arg(maxv));

            // 打印调试信息
            QByteArray head = buf.left(HDR_LEN + 32).toHex(' ');
            emit parseError("HEX(head+32): " + head);

            // 打印坏点的下标
            QStringList s;
            for (int k = 0; k < badIdx.size() && k < 10; ++k)
                s << QString::number(badIdx[k]);
            emit parseError("badIdx(first10)=" + s.join(","));

            // 打印第一个坏点附近的原始字节
            int i0 = badIdx[0];
            int byteOff = HDR_LEN + i0 * 2;
            int start = qMax(0, byteOff - 32);
            int end = qMin(buf.size(), byteOff + 64);
            QByteArray around = buf.mid(start, end - start).toHex(' ');
            emit parseError(QString("HEX(around bad) @%1: %2").arg(byteOff).arg(QString(around)));

            // 丢弃这一帧并继续同步
            buf.remove(0, 4);  // 丢弃整帧数据
            continue;
        }

        // 如果有坏数据，继续处理并打印调试信息
        emit frameReady(seq, type, samples);

        // 从缓冲区移除已处理的帧
        buf.remove(0, frameLen);
    }
}
