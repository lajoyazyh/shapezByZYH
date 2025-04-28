#ifndef STORESCENE_H
#define STORESCENE_H

#include <QMainWindow>
#include "ui_storescene.h"

namespace Ui {
class storescene;
}

class storescene : public QMainWindow
{
    Q_OBJECT

public:
    explicit storescene(QWidget *parent = nullptr);
    ~storescene();

    void setGold(int gold);
    void setOreCounts(int squareOreCount, int circleOreCount, int halfSquareOreCount, int halfCircleOreCount);

signals:
    void exchangeOreForGold();
    void buyDevice();
    void addDeliveryCenter();
    void addSource();

private slots:
    void onExchangeOreForGoldClicked();
    void onBuyDeviceClicked();
    void onAddDeliveryCenterClicked();
    void onAddSourceClicked();

private:
    Ui::storescene *ui;
};

#endif // STORESCENE_H
