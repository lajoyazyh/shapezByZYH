#ifndef UPGRADE_DIALOG_H
#define UPGRADE_DIALOG_H

#include <QDialog>
#include "ui_upgradedialog.h"  // 确保包含生成的 UI 类

namespace Ui {
class UpgradeDialog;
}

class UpgradeDialog : public QDialog {
    Q_OBJECT
public:
    explicit UpgradeDialog(QWidget *parent = nullptr);
    ~UpgradeDialog();

signals:
    void deviceUpgraded(const QString &deviceType);

private:
    Ui::UpgradeDialog *ui;
};

#endif // UPGRADE_DIALOG_H
