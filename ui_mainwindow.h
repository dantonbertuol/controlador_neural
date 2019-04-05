/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QDial *dialSetPoint;
    QPushButton *pushButton;
    QDoubleSpinBox *doubleSpinBoxSetPoint;
    QCheckBox *checkBoxRunning;
    QCustomPlot *widget;
    QPushButton *btnMid01;
    QPushButton *btnMid04;
    QPushButton *btnMid03;
    QPushButton *btnMid02;
    QPushButton *btnMid05;
    QPushButton *btnMid07;
    QPushButton *btnMid10;
    QPushButton *btnMid08;
    QPushButton *btnMid09;
    QPushButton *btnMid06;
    QPushButton *btnEntrada;
    QPushButton *btnSaida03;
    QPushButton *btnSaida01;
    QPushButton *btnSaida04;
    QPushButton *btnSaida02;
    QPushButton *btnSaida05;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line_3;
    QFrame *line_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(767, 488);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dialSetPoint = new QDial(centralWidget);
        dialSetPoint->setObjectName(QStringLiteral("dialSetPoint"));
        dialSetPoint->setGeometry(QRect(30, 0, 161, 121));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dialSetPoint->sizePolicy().hasHeightForWidth());
        dialSetPoint->setSizePolicy(sizePolicy);
        dialSetPoint->setMinimum(-100);
        dialSetPoint->setMaximum(100);
        dialSetPoint->setSingleStep(1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 130, 81, 23));
        doubleSpinBoxSetPoint = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxSetPoint->setObjectName(QStringLiteral("doubleSpinBoxSetPoint"));
        doubleSpinBoxSetPoint->setGeometry(QRect(70, 160, 81, 20));
        doubleSpinBoxSetPoint->setMinimum(-1);
        doubleSpinBoxSetPoint->setMaximum(1);
        doubleSpinBoxSetPoint->setSingleStep(0.01);
        checkBoxRunning = new QCheckBox(centralWidget);
        checkBoxRunning->setObjectName(QStringLiteral("checkBoxRunning"));
        checkBoxRunning->setGeometry(QRect(70, 190, 61, 17));
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 280, 721, 191));
        btnMid01 = new QPushButton(centralWidget);
        btnMid01->setObjectName(QStringLiteral("btnMid01"));
        btnMid01->setEnabled(false);
        btnMid01->setGeometry(QRect(350, 100, 31, 23));
        btnMid04 = new QPushButton(centralWidget);
        btnMid04->setObjectName(QStringLiteral("btnMid04"));
        btnMid04->setEnabled(false);
        btnMid04->setGeometry(QRect(470, 100, 31, 23));
        btnMid03 = new QPushButton(centralWidget);
        btnMid03->setObjectName(QStringLiteral("btnMid03"));
        btnMid03->setEnabled(false);
        btnMid03->setGeometry(QRect(430, 100, 31, 23));
        btnMid02 = new QPushButton(centralWidget);
        btnMid02->setObjectName(QStringLiteral("btnMid02"));
        btnMid02->setEnabled(false);
        btnMid02->setGeometry(QRect(390, 100, 31, 23));
        btnMid05 = new QPushButton(centralWidget);
        btnMid05->setObjectName(QStringLiteral("btnMid05"));
        btnMid05->setEnabled(false);
        btnMid05->setGeometry(QRect(510, 100, 31, 23));
        btnMid07 = new QPushButton(centralWidget);
        btnMid07->setObjectName(QStringLiteral("btnMid07"));
        btnMid07->setEnabled(false);
        btnMid07->setGeometry(QRect(590, 100, 31, 23));
        btnMid10 = new QPushButton(centralWidget);
        btnMid10->setObjectName(QStringLiteral("btnMid10"));
        btnMid10->setEnabled(false);
        btnMid10->setGeometry(QRect(710, 100, 31, 23));
        btnMid08 = new QPushButton(centralWidget);
        btnMid08->setObjectName(QStringLiteral("btnMid08"));
        btnMid08->setEnabled(false);
        btnMid08->setGeometry(QRect(630, 100, 31, 23));
        btnMid09 = new QPushButton(centralWidget);
        btnMid09->setObjectName(QStringLiteral("btnMid09"));
        btnMid09->setEnabled(false);
        btnMid09->setGeometry(QRect(670, 100, 31, 23));
        btnMid06 = new QPushButton(centralWidget);
        btnMid06->setObjectName(QStringLiteral("btnMid06"));
        btnMid06->setEnabled(false);
        btnMid06->setGeometry(QRect(550, 100, 31, 23));
        btnEntrada = new QPushButton(centralWidget);
        btnEntrada->setObjectName(QStringLiteral("btnEntrada"));
        btnEntrada->setEnabled(false);
        btnEntrada->setGeometry(QRect(530, 40, 31, 23));
        btnEntrada->setStyleSheet(QStringLiteral(""));
        btnSaida03 = new QPushButton(centralWidget);
        btnSaida03->setObjectName(QStringLiteral("btnSaida03"));
        btnSaida03->setEnabled(false);
        btnSaida03->setGeometry(QRect(530, 160, 31, 23));
        btnSaida01 = new QPushButton(centralWidget);
        btnSaida01->setObjectName(QStringLiteral("btnSaida01"));
        btnSaida01->setEnabled(false);
        btnSaida01->setGeometry(QRect(450, 160, 31, 23));
        btnSaida04 = new QPushButton(centralWidget);
        btnSaida04->setObjectName(QStringLiteral("btnSaida04"));
        btnSaida04->setEnabled(false);
        btnSaida04->setGeometry(QRect(570, 160, 31, 23));
        btnSaida02 = new QPushButton(centralWidget);
        btnSaida02->setObjectName(QStringLiteral("btnSaida02"));
        btnSaida02->setEnabled(false);
        btnSaida02->setGeometry(QRect(490, 160, 31, 23));
        btnSaida05 = new QPushButton(centralWidget);
        btnSaida05->setObjectName(QStringLiteral("btnSaida05"));
        btnSaida05->setEnabled(false);
        btnSaida05->setGeometry(QRect(610, 160, 31, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(246, 40, 71, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(246, 100, 91, 20));
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 160, 41, 20));
        label_3->setFont(font);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(20, 240, 721, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(220, 20, 20, 191));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Treinar", nullptr));
        checkBoxRunning->setText(QApplication::translate("MainWindow", "Executar", nullptr));
        btnMid01->setText(QString());
        btnMid04->setText(QString());
        btnMid03->setText(QString());
        btnMid02->setText(QString());
        btnMid05->setText(QString());
        btnMid07->setText(QString());
        btnMid10->setText(QString());
        btnMid08->setText(QString());
        btnMid09->setText(QString());
        btnMid06->setText(QString());
        btnEntrada->setText(QString());
        btnSaida03->setText(QString());
        btnSaida01->setText(QString());
        btnSaida04->setText(QString());
        btnSaida02->setText(QString());
        btnSaida05->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Entrada", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Intermedi\303\241ria", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Sa\303\255da", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
