#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);//初始化
    refreshPorts();
    initPlot();
    CollectThread();
}
MainWindow::~MainWindow()
{
    if (parserThread) {
        parserThread->quit();
        parserThread->wait();
    }
    delete ui;
}
//启动采集线程
void MainWindow::CollectThread(){
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::onSerialReadyRead);

    // 启动解析线程
    parserThread = new QThread(this);
    parser = new Frame();
    parser->moveToThread(parserThread);

    connect(this, &MainWindow::destroyed, parserThread, &QThread::quit);
    connect(parserThread, &QThread::finished, parser, &QObject::deleteLater);

    connect(this, &MainWindow::feedToParser, parser, &Frame::feed, Qt::QueuedConnection);
    connect(parser, &Frame::frameReady, this, &MainWindow::onFrameReady);
    connect(parser, &Frame::parseError, this, [](const QString &e){
        qDebug() << "parseError:" << e;
    });

    parserThread->start();

}
//刷新端口
void MainWindow::refreshPorts(){
    ui->serialport->clear();
    // 枚举所有可用串口
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports)
    {
        QString text = info.portName();
        if (!info.description().isEmpty())
            text += " - " + info.description();
        ui->serialport->addItem(text, info.portName());
    }
}
//波形初始化
void MainWindow::initPlot()
{
    // 关键：先创建两条曲线
    ui->plotwidget->addGraph(); // graph(0) -> CH0
    ui->plotwidget->addGraph(); // graph(1) -> CH1

    //两个控件控制波形显示与否
    ui->CH1->setChecked(true);
    ui->CH2->setChecked(true);
    connect(ui->CH1, &QCheckBox::toggled, this, [=](bool on){
        ui->plotwidget->graph(0)->setVisible(on);
        ui->plotwidget->replot(QCustomPlot::rpQueuedReplot);
    });

    connect(ui->CH2, &QCheckBox::toggled, this, [=](bool on){
        ui->plotwidget->graph(1)->setVisible(on);
        ui->plotwidget->replot(QCustomPlot::rpQueuedReplot);
    });

    ui->plotwidget->xAxis->setLabel("Sample");
    ui->plotwidget->yAxis->setLabel("ADC");

    ui->plotwidget->graph(0)->setName("CH1");
    ui->plotwidget->graph(1)->setName("CH2");

    ui->plotwidget->graph(0)->setPen(QPen(Qt::red, 2));
    ui->plotwidget->graph(1)->setPen(QPen(Qt::blue, 2));

    ui->plotwidget->xAxis->setLabel("Sample");
    ui->plotwidget->yAxis->setLabel("Voltage (V)");

    ui->plotwidget->legend->setVisible(true);

    ui->plotwidget->rescaleAxes();
    ui->plotwidget->replot();

    m_plotContextMenu = new PlotContextMenu(ui->plotwidget, this);//右键菜单
    connect(ui->plotwidget, &QCustomPlot::customContextMenuRequested,m_plotContextMenu, &PlotContextMenu::handleContextMenuRequest);
    connect(ui->plotwidget, &QCustomPlot::mouseMove, m_plotContextMenu, &PlotContextMenu::onsyMouseMove);

}
//连接串口
void MainWindow::on_connect_clicked(bool checked)
{
    if(checked){
        QString portName = ui->serialport->currentData().toString();
        if (portName.isEmpty())
        {
            QMessageBox::warning(this, "错误", "请选择串口！");
            return;
        }
        serial->setPortName(portName);
        //串口参数
        serial->setBaudRate(QSerialPort::Baud115200);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if (!serial->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, "连接失败",
                                  "无法打开串口 " + portName +
                                  "\n" + serial->errorString());
            return;
        }
        ui->serialport->setEnabled(false);
        ui->connect->setText("断开");
    }else{
        if (serial->isOpen())
        {
            serial->close();
            ui->serialport->setEnabled(true);
            ui->connect->setText("连接");
            return;
        }
    }
}
//选择采样模式开始采集
void MainWindow::on_startadc_clicked()
{
    if (!serial || !serial->isOpen()) {
        QMessageBox::warning(this, "提示", "请先连接串口！");
        return;
    }

    collectchoice = ui->ADCmode->currentIndex();
    qDebug() << "采集模式" << collectchoice;

    QByteArray cmd = collectchoice ? "STARTADC2\r\n" : "STARTADC1\r\n";

    qint64 n = serial->write(cmd);
    if (n != cmd.size()) {
        QMessageBox::warning(this, "发送失败", "串口写入不完整！");
        return;
    }

    serial->waitForBytesWritten(100);

    ui->startadc->setEnabled(false);
    ui->stopadc->setEnabled(true);
}
//停止采集
void MainWindow::on_stopadc_clicked()
{
    if (!serial || !serial->isOpen()) {
        QMessageBox::warning(this, "提示", "串口未连接！");
        return;
    }

    int collectchoice = ui->ADCmode->currentIndex();
    QByteArray cmd = collectchoice ? "STOPADC2\r\n" : "STOPADC1\r\n";

    serial->write(cmd);
    serial->waitForBytesWritten(100);

    ui->startadc->setEnabled(true);
}
//读取串口数据
void MainWindow::onSerialReadyRead()
{
    QByteArray data = serial->readAll();
    SerialRate(data);
    if (!data.isEmpty())
        emit feedToParser(data); // 进入解析线程
}
//画图
void MainWindow::onFrameReady(quint16 seq, quint8 type, QVector<quint16> samples)
{
    //qDebug() << "Frame:" << "seq=" << seq << "type=" << type << "N=" << samples.size();
    // 下一步：把 samples 转成 x/y，送到你的绘图控件
    const int N = samples.size();
    if (N < 2) return;

    const int nPair = N / 2; // 每个通道点数
    QVector<double> x(nPair), y0(nPair), y1(nPair);
    const double Vref = 3.3;
    const double ADC_MAX = 4095.0;
    for (int i = 0; i < nPair; ++i) {
        x[i]  = i;
        y0[i] = samples[2*i]     * Vref / ADC_MAX;
        y1[i] = samples[2*i + 1] * Vref / ADC_MAX;
    }

    if (ui->CH1->isChecked())
        ui->plotwidget->graph(0)->setData(x, y0);
    if (ui->CH2->isChecked())
        ui->plotwidget->graph(1)->setData(x, y1);

    ui->plotwidget->rescaleAxes(true);
    ui->plotwidget->yAxis->setRangeLower(0.0);
    ui->plotwidget->replot(QCustomPlot::rpQueuedReplot);
}
//测速
void MainWindow::SerialRate(QByteArray data)
{
    static qint64 bytes = 0;
    static QElapsedTimer t;

    if (!t.isValid()) t.start();

    bytes += data.size();   // data = 每次收到的 QByteArray

    if (t.elapsed() >= 1000) {
        qDebug() << "USB 实际速率 =" << bytes / 1024.0 << "KB/s";
        bytes = 0;
        t.restart();
    }
}
//******************************************DAC****************************************
//开始DAC
void MainWindow::on_startdac_clicked()
{
    if (!serial || !serial->isOpen()) {
        QMessageBox::warning(this, "提示", "请先连接串口！");
        return;
    }
    dacchoice=ui->DACmode->currentIndex();
    QByteArray cmd;
    if (dacchoice == 0) {
        cmd = "STARTDAC1\r\n";
    } else {
        int n = ui->dacnum->value();
        if (n <= 0) {
            QMessageBox::warning(this, "参数错误", "脉冲个数必须大于 0！");
            return;
        }
        cmd = QByteArray("STARTDAC2 ") + QByteArray::number(n) + "\r\n";
    }

    qint64 w = serial->write(cmd);
    if (w != cmd.size()) {
        QMessageBox::warning(this, "发送失败", "串口写入不完整！");
        return;
    }
    serial->waitForBytesWritten(100);
}
//停止DAC
void MainWindow::on_stopdac_clicked()
{
    if (!serial || !serial->isOpen()) {
        QMessageBox::warning(this, "提示", "串口未连接！");
        return;
    }

    int dacchoice = ui->DACmode->currentIndex();
    QByteArray cmd = dacchoice ? "STOPDAC2\r\n" : "STOPDAC1\r\n";

    serial->write(cmd);
    serial->waitForBytesWritten(100);
}
void MainWindow::on_DACmode_currentIndexChanged(int index)
{
    if(index==0){
        ui->dacnum->setEnabled(false);
    }else{
        ui->dacnum->setEnabled(true);
    }
}
