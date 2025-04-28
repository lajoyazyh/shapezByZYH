#include "storescene.h"
#include "ui_storescene.h"

storescene::storescene(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::storescene)
{
    ui->setupUi(this);
    setWindowTitle("Store");

    // 连接信号和槽
    connect(ui->exchangeButton, &QPushButton::clicked, this, &storescene::onExchangeOreForGoldClicked);
    connect(ui->buyDeviceButton, &QPushButton::clicked, this, &storescene::onBuyDeviceClicked);
    connect(ui->addDeliveryCenterButton, &QPushButton::clicked, this, &storescene::onAddDeliveryCenterClicked);
    connect(ui->addSourceButton, &QPushButton::clicked, this, &storescene::onAddSourceClicked);
}

storescene::~storescene()
{
    delete ui;
}

void storescene::setGold(int gold)
{
    ui->goldLabel->setText(QString("Gold: %1").arg(gold));
}

void storescene::setOreCounts(int squareOreCount, int circleOreCount, int halfSquareOreCount, int halfCircleOreCount)
{
    ui->squareOreLabel->setText(QString("Square Ores: %1").arg(squareOreCount));
    ui->circleOreLabel->setText(QString("Circle Ores: %1").arg(circleOreCount));
    ui->halfSquareOreLabel->setText(QString("Half Square Ores: %1").arg(halfSquareOreCount));
    ui->halfCircleOreLabel->setText(QString("Half Circle Ores: %1").arg(halfCircleOreCount));
}

void storescene::onExchangeOreForGoldClicked()
{
    emit exchangeOreForGold();
}

void storescene::onBuyDeviceClicked()
{
    emit buyDevice();
}

void storescene::onAddDeliveryCenterClicked()
{
    emit addDeliveryCenter();
}

void storescene::onAddSourceClicked()
{
    emit addSource();
}
