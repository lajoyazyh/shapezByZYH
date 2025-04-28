/********************************************************************************
** Form generated from reading UI file 'gamescene.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESCENE_H
#define UI_GAMESCENE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamescene
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonMiner;
    QPushButton *pushButtonConveyorBelt;
    QPushButton *pushButtonTrashBin;
    QPushButton *pushButtonCutter;
    QPushButton *pushButtonTask5;
    QPushButton *pushButtonShop;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gamescene)
    {
        if (gamescene->objectName().isEmpty())
            gamescene->setObjectName("gamescene");
        gamescene->resize(1000, 800);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/resource/images/starticon.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        gamescene->setWindowIcon(icon);
        gamescene->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(gamescene);
        centralwidget->setObjectName("centralwidget");
        pushButtonMiner = new QPushButton(centralwidget);
        pushButtonMiner->setObjectName("pushButtonMiner");
        pushButtonMiner->setGeometry(QRect(60, 583, 75, 75));
        pushButtonMiner->setAutoFillBackground(false);
        pushButtonMiner->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/miner_east.png);\n"
""));
        pushButtonConveyorBelt = new QPushButton(centralwidget);
        pushButtonConveyorBelt->setObjectName("pushButtonConveyorBelt");
        pushButtonConveyorBelt->setGeometry(QRect(210, 580, 75, 75));
        pushButtonConveyorBelt->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/conveyor_belt_east.png);"));
        pushButtonTrashBin = new QPushButton(centralwidget);
        pushButtonTrashBin->setObjectName("pushButtonTrashBin");
        pushButtonTrashBin->setGeometry(QRect(360, 580, 75, 75));
        pushButtonTrashBin->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/trash.png);"));
        pushButtonCutter = new QPushButton(centralwidget);
        pushButtonCutter->setObjectName("pushButtonCutter");
        pushButtonCutter->setGeometry(QRect(510, 580, 75, 75));
        pushButtonCutter->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/images/resource/images/cutter.png);"));
        pushButtonTask5 = new QPushButton(centralwidget);
        pushButtonTask5->setObjectName("pushButtonTask5");
        pushButtonTask5->setGeometry(QRect(630, 670, 241, 75));
        QFont font;
        font.setFamilies({QString::fromUtf8("Haettenschweiler")});
        font.setPointSize(18);
        pushButtonTask5->setFont(font);
        pushButtonShop = new QPushButton(centralwidget);
        pushButtonShop->setObjectName("pushButtonShop");
        pushButtonShop->setGeometry(QRect(630, 580, 91, 71));
        pushButtonShop->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/shop.png);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(770, 580, 91, 71));
        gamescene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gamescene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        gamescene->setMenuBar(menubar);
        statusbar = new QStatusBar(gamescene);
        statusbar->setObjectName("statusbar");
        gamescene->setStatusBar(statusbar);

        retranslateUi(gamescene);

        QMetaObject::connectSlotsByName(gamescene);
    } // setupUi

    void retranslateUi(QMainWindow *gamescene)
    {
        gamescene->setWindowTitle(QCoreApplication::translate("gamescene", "Game Scene", nullptr));
        pushButtonMiner->setText(QString());
        pushButtonConveyorBelt->setText(QString());
        pushButtonTrashBin->setText(QString());
        pushButtonCutter->setText(QString());
        pushButtonTask5->setText(QCoreApplication::translate("gamescene", "Accept new task (time limited)", nullptr));
        pushButtonShop->setText(QString());
        pushButton->setText(QCoreApplication::translate("gamescene", "Mutiplier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamescene: public Ui_gamescene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCENE_H
