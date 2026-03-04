#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QThread>

#include "frame.h"
#include "PlotContextMenu/plotcontextmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void feedToParser(const QByteArray &data);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void refreshPorts();
    void initPlot();
    void on_connect_clicked(bool checked);
    void on_startadc_clicked();
    void on_stopadc_clicked();

    void CollectThread();
    void onSerialReadyRead();
    void onFrameReady(quint16 seq, quint8 type, QVector<quint16> samples);
    void SerialRate(QByteArray data);

    void on_startdac_clicked();

    void on_stopdac_clicked();

    void on_DACmode_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial; //串口对象
    int collectchoice=0;
    int dacchoice=0;

    QThread *parserThread = nullptr;
    Frame *parser = nullptr;

    PlotContextMenu* m_plotContextMenu;             //鼠标右键菜单
};
#endif // MAINWINDOW_H
