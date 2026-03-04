#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QByteArray>
#include <QVector>
#include <QDebug>
class Frame : public QObject
{
    Q_OBJECT
public:
    explicit Frame(QObject *parent = nullptr);

public slots:
    void feed(const QByteArray &data);
signals:
    void frameReady(quint16 seq, quint8 type, QVector<quint16> samples);
    void parseError(const QString &msg);
private:
    QByteArray buf;

       static quint16 rd_u16_le(const uchar *p) {
           return (quint16)p[0] | ((quint16)p[1] << 8);
       }
       static quint32 rd_u32_le(const uchar *p) {
           return (quint32)p[0] | ((quint32)p[1] << 8) | ((quint32)p[2] << 16) | ((quint32)p[3] << 24);
       }

};

#endif // FRAME_H
