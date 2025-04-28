/********************************************************************************
** Form generated from reading UI file 'upgrade_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPGRADE_DIALOG_H
#define UI_UPGRADE_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_upgrade_dialog
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonMiner;
    QPushButton *pushButtonConveyorBelt;
    QPushButton *pushButtonCutter;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *upgrade_dialog)
    {
        if (upgrade_dialog->objectName().isEmpty())
            upgrade_dialog->setObjectName("upgrade_dialog");
        upgrade_dialog->resize(800, 600);
        centralwidget = new QWidget(upgrade_dialog);
        centralwidget->setObjectName("centralwidget");
        pushButtonMiner = new QPushButton(centralwidget);
        pushButtonMiner->setObjectName("pushButtonMiner");
        pushButtonMiner->setGeometry(QRect(120, 120, 75, 24));
        pushButtonConveyorBelt = new QPushButton(centralwidget);
        pushButtonConveyorBelt->setObjectName("pushButtonConveyorBelt");
        pushButtonConveyorBelt->setGeometry(QRect(120, 180, 75, 24));
        pushButtonCutter = new QPushButton(centralwidget);
        pushButtonCutter->setObjectName("pushButtonCutter");
        pushButtonCutter->setGeometry(QRect(120, 240, 75, 24));
        upgrade_dialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(upgrade_dialog);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        upgrade_dialog->setMenuBar(menubar);
        statusbar = new QStatusBar(upgrade_dialog);
        statusbar->setObjectName("statusbar");
        upgrade_dialog->setStatusBar(statusbar);

        retranslateUi(upgrade_dialog);

        QMetaObject::connectSlotsByName(upgrade_dialog);
    } // setupUi

    void retranslateUi(QMainWindow *upgrade_dialog)
    {
        upgrade_dialog->setWindowTitle(QCoreApplication::translate("upgrade_dialog", "MainWindow", nullptr));
        pushButtonMiner->setText(QCoreApplication::translate("upgrade_dialog", "PushButtonMiner", nullptr));
        pushButtonConveyorBelt->setText(QCoreApplication::translate("upgrade_dialog", "PushButtonbelt", nullptr));
        pushButtonCutter->setText(QCoreApplication::translate("upgrade_dialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class upgrade_dialog: public Ui_upgrade_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPGRADE_DIALOG_H
