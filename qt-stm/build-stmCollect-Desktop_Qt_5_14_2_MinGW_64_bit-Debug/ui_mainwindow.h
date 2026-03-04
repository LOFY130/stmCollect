/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *serialport;
    QPushButton *connect;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *ADCmode;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *startadc;
    QPushButton *stopadc;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *CH1;
    QCheckBox *CH2;
    QCustomPlot *plotwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QComboBox *DACmode;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QSpinBox *dacnum;
    QVBoxLayout *verticalLayout_3;
    QPushButton *startdac;
    QPushButton *stopdac;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(925, 723);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        serialport = new QComboBox(centralwidget);
        serialport->setObjectName(QString::fromUtf8("serialport"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(serialport->sizePolicy().hasHeightForWidth());
        serialport->setSizePolicy(sizePolicy);
        serialport->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(serialport);


        horizontalLayout_4->addLayout(horizontalLayout);

        connect = new QPushButton(centralwidget);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setMinimumSize(QSize(0, 35));
        connect->setCheckable(true);

        horizontalLayout_4->addWidget(connect);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        ADCmode = new QComboBox(centralwidget);
        ADCmode->addItem(QString());
        ADCmode->addItem(QString());
        ADCmode->setObjectName(QString::fromUtf8("ADCmode"));
        sizePolicy.setHeightForWidth(ADCmode->sizePolicy().hasHeightForWidth());
        ADCmode->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(ADCmode);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        startadc = new QPushButton(centralwidget);
        startadc->setObjectName(QString::fromUtf8("startadc"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startadc->sizePolicy().hasHeightForWidth());
        startadc->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(startadc);

        stopadc = new QPushButton(centralwidget);
        stopadc->setObjectName(QString::fromUtf8("stopadc"));
        sizePolicy1.setHeightForWidth(stopadc->sizePolicy().hasHeightForWidth());
        stopadc->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(stopadc);


        horizontalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        CH1 = new QCheckBox(centralwidget);
        CH1->setObjectName(QString::fromUtf8("CH1"));
        sizePolicy1.setHeightForWidth(CH1->sizePolicy().hasHeightForWidth());
        CH1->setSizePolicy(sizePolicy1);
        CH1->setMinimumSize(QSize(0, 35));

        horizontalLayout_6->addWidget(CH1);

        CH2 = new QCheckBox(centralwidget);
        CH2->setObjectName(QString::fromUtf8("CH2"));
        sizePolicy1.setHeightForWidth(CH2->sizePolicy().hasHeightForWidth());
        CH2->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(CH2);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout);

        plotwidget = new QCustomPlot(centralwidget);
        plotwidget->setObjectName(QString::fromUtf8("plotwidget"));

        verticalLayout_2->addWidget(plotwidget);

        verticalLayout_2->setStretch(1, 1);

        verticalLayout_6->addLayout(verticalLayout_2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        DACmode = new QComboBox(groupBox);
        DACmode->addItem(QString());
        DACmode->addItem(QString());
        DACmode->setObjectName(QString::fromUtf8("DACmode"));

        horizontalLayout_7->addWidget(DACmode);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_9->addWidget(label_4);

        dacnum = new QSpinBox(groupBox);
        dacnum->setObjectName(QString::fromUtf8("dacnum"));

        horizontalLayout_9->addWidget(dacnum);


        verticalLayout_4->addLayout(horizontalLayout_9);


        horizontalLayout_8->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        startdac = new QPushButton(groupBox);
        startdac->setObjectName(QString::fromUtf8("startdac"));

        verticalLayout_3->addWidget(startdac);

        stopdac = new QPushButton(groupBox);
        stopdac->setObjectName(QString::fromUtf8("stopdac"));

        verticalLayout_3->addWidget(stopdac);


        horizontalLayout_8->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_8);


        verticalLayout_6->addWidget(groupBox);


        verticalLayout_7->addLayout(verticalLayout_6);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 925, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\351\200\211\346\213\251", nullptr));
        connect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\346\250\241\345\274\217", nullptr));
        ADCmode->setItemText(0, QCoreApplication::translate("MainWindow", "\350\277\236\347\273\255\351\207\207\351\233\206", nullptr));
        ADCmode->setItemText(1, QCoreApplication::translate("MainWindow", "\345\244\226\351\203\250\350\247\246\345\217\221", nullptr));

        startadc->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        stopadc->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        CH1->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231", nullptr));
        CH2->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "DAC", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\347\261\273\345\236\213", nullptr));
        DACmode->setItemText(0, QCoreApplication::translate("MainWindow", "\346\255\243\345\274\246\344\277\241\345\217\267", nullptr));
        DACmode->setItemText(1, QCoreApplication::translate("MainWindow", "\350\204\211\345\206\262\345\274\217\346\255\243\345\274\246\344\277\241\345\217\267", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "\350\204\211\345\206\262\346\225\260", nullptr));
        startdac->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        stopdac->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
