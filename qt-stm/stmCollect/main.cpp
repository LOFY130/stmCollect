#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QVector<quint16>>("QVector<quint16>");
    MainWindow w;
    w.show();
    return a.exec();
}
