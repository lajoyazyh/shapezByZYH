/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScene
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainScene)
    {
        if (MainScene->objectName().isEmpty())
            MainScene->setObjectName("MainScene");
        MainScene->resize(1000, 800);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/resource/images/starticon.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainScene->setWindowIcon(icon);
        centralwidget = new QWidget(MainScene);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 1000, 800));
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/shapez.jpg);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 470, 300, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("IQYHT")});
        font.setPointSize(20);
        font.setBold(true);
        font.setUnderline(false);
        pushButton->setFont(font);
        MainScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainScene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        MainScene->setMenuBar(menubar);
        statusbar = new QStatusBar(MainScene);
        statusbar->setObjectName("statusbar");
        MainScene->setStatusBar(statusbar);

        retranslateUi(MainScene);

        QMetaObject::connectSlotsByName(MainScene);
    } // setupUi

    void retranslateUi(QMainWindow *MainScene)
    {
        MainScene->setWindowTitle(QCoreApplication::translate("MainScene", "Welcome to Shapez (By Zhu Yh)", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainScene", "Start New Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainScene: public Ui_MainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
