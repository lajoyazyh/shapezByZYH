/********************************************************************************
** Form generated from reading UI file 'upgradedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPGRADEDIALOG_H
#define UI_UPGRADEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UpgradeDialog
{
public:
    QPushButton *conveyorButton;
    QPushButton *minerButton;
    QPushButton *cutterButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *UpgradeDialog)
    {
        if (UpgradeDialog->objectName().isEmpty())
            UpgradeDialog->setObjectName("UpgradeDialog");
        UpgradeDialog->resize(400, 300);
        conveyorButton = new QPushButton(UpgradeDialog);
        conveyorButton->setObjectName("conveyorButton");
        conveyorButton->setGeometry(QRect(45, 120, 70, 70));
        conveyorButton->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/conveyor_belt_east.png);"));
        minerButton = new QPushButton(UpgradeDialog);
        minerButton->setObjectName("minerButton");
        minerButton->setGeometry(QRect(165, 120, 70, 70));
        minerButton->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/miner_east.png);"));
        cutterButton = new QPushButton(UpgradeDialog);
        cutterButton->setObjectName("cutterButton");
        cutterButton->setGeometry(QRect(285, 120, 70, 70));
        cutterButton->setStyleSheet(QString::fromUtf8("image: url(:/images/resource/images/cutter.png);"));
        label = new QLabel(UpgradeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 200, 61, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200")});
        font.setPointSize(16);
        label->setFont(font);
        label_2 = new QLabel(UpgradeDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 200, 61, 21));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_3 = new QLabel(UpgradeDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 200, 61, 21));
        label_3->setFont(font);
        label_4 = new QLabel(UpgradeDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 60, 351, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("STCaiyun")});
        font1.setPointSize(16);
        label_4->setFont(font1);

        retranslateUi(UpgradeDialog);

        QMetaObject::connectSlotsByName(UpgradeDialog);
    } // setupUi

    void retranslateUi(QDialog *UpgradeDialog)
    {
        UpgradeDialog->setWindowTitle(QCoreApplication::translate("UpgradeDialog", "Dialog", nullptr));
        conveyorButton->setText(QString());
        minerButton->setText(QString());
        cutterButton->setText(QString());
        label->setText(QCoreApplication::translate("UpgradeDialog", "belt", nullptr));
        label_2->setText(QCoreApplication::translate("UpgradeDialog", "miner", nullptr));
        label_3->setText(QCoreApplication::translate("UpgradeDialog", "cutter", nullptr));
        label_4->setText(QCoreApplication::translate("UpgradeDialog", "choose a device you hope to upgrade", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UpgradeDialog: public Ui_UpgradeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPGRADEDIALOG_H
