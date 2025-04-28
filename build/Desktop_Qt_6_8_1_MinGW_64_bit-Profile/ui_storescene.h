/********************************************************************************
** Form generated from reading UI file 'storescene.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STORESCENE_H
#define UI_STORESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_storescene
{
public:
    QWidget *centralwidget;
    QPushButton *exchangeButton;
    QPushButton *buyDeviceButton;
    QPushButton *addDeliveryCenterButton;
    QPushButton *addSourceButton;
    QLabel *goldLabel;
    QLabel *squareOreLabel;
    QLabel *circleOreLabel;
    QLabel *halfSquareOreLabel;
    QLabel *halfCircleOreLabel;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *storescene)
    {
        if (storescene->objectName().isEmpty())
            storescene->setObjectName("storescene");
        storescene->resize(750, 900);
        centralwidget = new QWidget(storescene);
        centralwidget->setObjectName("centralwidget");
        exchangeButton = new QPushButton(centralwidget);
        exchangeButton->setObjectName("exchangeButton");
        exchangeButton->setGeometry(QRect(100, 250, 541, 81));
        buyDeviceButton = new QPushButton(centralwidget);
        buyDeviceButton->setObjectName("buyDeviceButton");
        buyDeviceButton->setGeometry(QRect(100, 410, 541, 71));
        addDeliveryCenterButton = new QPushButton(centralwidget);
        addDeliveryCenterButton->setObjectName("addDeliveryCenterButton");
        addDeliveryCenterButton->setGeometry(QRect(100, 710, 541, 71));
        addSourceButton = new QPushButton(centralwidget);
        addSourceButton->setObjectName("addSourceButton");
        addSourceButton->setGeometry(QRect(100, 550, 541, 71));
        goldLabel = new QLabel(centralwidget);
        goldLabel->setObjectName("goldLabel");
        goldLabel->setGeometry(QRect(50, 50, 200, 50));
        squareOreLabel = new QLabel(centralwidget);
        squareOreLabel->setObjectName("squareOreLabel");
        squareOreLabel->setGeometry(QRect(50, 100, 200, 50));
        circleOreLabel = new QLabel(centralwidget);
        circleOreLabel->setObjectName("circleOreLabel");
        circleOreLabel->setGeometry(QRect(340, 100, 200, 50));
        halfSquareOreLabel = new QLabel(centralwidget);
        halfSquareOreLabel->setObjectName("halfSquareOreLabel");
        halfSquareOreLabel->setGeometry(QRect(50, 150, 200, 50));
        halfCircleOreLabel = new QLabel(centralwidget);
        halfCircleOreLabel->setObjectName("halfCircleOreLabel");
        halfCircleOreLabel->setGeometry(QRect(340, 150, 200, 50));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 750, 900));
        label->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/shop_scene.png);"));
        storescene->setCentralWidget(centralwidget);
        label->raise();
        exchangeButton->raise();
        buyDeviceButton->raise();
        addDeliveryCenterButton->raise();
        addSourceButton->raise();
        goldLabel->raise();
        squareOreLabel->raise();
        circleOreLabel->raise();
        halfSquareOreLabel->raise();
        halfCircleOreLabel->raise();
        menubar = new QMenuBar(storescene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 750, 22));
        storescene->setMenuBar(menubar);
        statusbar = new QStatusBar(storescene);
        statusbar->setObjectName("statusbar");
        storescene->setStatusBar(statusbar);

        retranslateUi(storescene);

        QMetaObject::connectSlotsByName(storescene);
    } // setupUi

    void retranslateUi(QMainWindow *storescene)
    {
        storescene->setWindowTitle(QCoreApplication::translate("storescene", "MainWindow", nullptr));
        exchangeButton->setText(QCoreApplication::translate("storescene", "Exchange {1 square + 1 circle + 2 half square + 2 half circle} for 10 gold coins", nullptr));
        buyDeviceButton->setText(QCoreApplication::translate("storescene", "buyDeviceButton", nullptr));
        addDeliveryCenterButton->setText(QCoreApplication::translate("storescene", "addDeliveryCenterButton", nullptr));
        addSourceButton->setText(QCoreApplication::translate("storescene", "addSourceButton", nullptr));
        goldLabel->setText(QCoreApplication::translate("storescene", "gold num", nullptr));
        squareOreLabel->setText(QCoreApplication::translate("storescene", "square num", nullptr));
        circleOreLabel->setText(QCoreApplication::translate("storescene", "circle num", nullptr));
        halfSquareOreLabel->setText(QCoreApplication::translate("storescene", "half square num", nullptr));
        halfCircleOreLabel->setText(QCoreApplication::translate("storescene", "half circle num", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class storescene: public Ui_storescene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STORESCENE_H
