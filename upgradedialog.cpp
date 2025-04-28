#include "upgradedialog.h"
#include "ui_upgradedialog.h"

UpgradeDialog::UpgradeDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::UpgradeDialog) {
    ui->setupUi(this);

    connect(ui->conveyorButton, &QPushButton::clicked, this, [this](){
        emit deviceUpgraded("ConveyorBelt");
        accept();
    });

    connect(ui->minerButton, &QPushButton::clicked, this, [this](){
        emit deviceUpgraded("Miner");
        accept();
    });

    connect(ui->cutterButton, &QPushButton::clicked, this, [this](){
        emit deviceUpgraded("Cutter");
        accept();
    });
}

UpgradeDialog::~UpgradeDialog() {
    delete ui;
}
