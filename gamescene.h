#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "map.h"
#include "source.h"
#include "miner.h"
#include "conveyorbelt.h"
#include "cutter.h"
#include "trashbin.h"
#include "directions.h"
#include "storescene.h"
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QIODevice>

namespace Ui {
class gamescene;
}

class gamescene : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamescene(QWidget *parent = nullptr);
    ~gamescene();

    void loadGameProgress(const QString& filePath);  // 添加加载存档的函数

    int getOreCount() const { return squareOreCount + circleOreCount + halfSquareOreCount + halfCircleOreCount; }
    int getGold() const { return gold_; }
    void setGold(int gold) { gold_ = gold; }
    void addDevice(int deviceType);
    void addDeliveryCenter(int x, int y, int width, int height);
    void addSource(int x, int y, Source::Type type);
    void showStore();  // 显示商店界面
    void clearOres();


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButtonMiner_clicked(); // Miner button
    void on_pushButtonConveyorBelt_clicked(); // ConveyorBelt button
    void on_pushButtonTrashBin_clicked(); // TrashBin button
    void on_pushButtonCutter_clicked(); // Cutter button
    void updateGame(); // 更新游戏状态和ConveyorBelt状态
    void updateMiner(); // 更新 Miner 状态
    void updateCutter(); // 更新 Cutter 状态
    void updateTrashBin(); // 更新 TrashBin 状态
    void on_pushButtonTask5_clicked(); // 任务5按钮
    void startTask5Timer(); // 开始任务5计时
    void checkTask5Completion();
    void upgradeDevice(const QString &deviceType);  // 声明槽函数

    void on_pushButtonShop_clicked(); // 商店按钮
    void onExchangeOreForGold();  // 兑换金币
    void onBuyDevice();  // 购买设备
    void onAddDeliveryCenter();  // 增加交易中心
    void onAddSource();  // 增加源头


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::gamescene *ui;
    Map map;  // 地图对象
    Miner miner;  // 开采器
    ConveyorBelt conveyorBelt;  // 传送带
    Cutter cutter;  // 切割机
    TrashBin trashBin;  // 垃圾桶
    int selectedDeviceType = 0;  // 当前选中的设备类型
    Direction selectedDirection = EAST;  // 当前选中的设备方向，默认东
    QTimer timer;  // 定时器，控制整体和ConveyorBelt更新
    QTimer minerTimer;  // 定时器，控制 Miner 更新
    QTimer cutterTimer;  // 定时器，控制 Cutter 更新
    QTimer trashBinTimer;  // 定时器，控制 TrashBin 更新
    int squareOreCount = 0;  // 方形矿物数量
    int circleOreCount = 0;  // 圆形矿物数量
    int halfSquareOreCount = 0;
    int halfCircleOreCount = 0;
    int task5SquareOreCount = 0;  // 任务5：交付的方形ore数量
    int task5CircleOreCount = 0;  // 任务5：交付的圆形ore数量
    int task5HalfSquareOreCount = 0;  // 任务5：交付的半个方形ore数量
    int task5HalfCircleOreCount = 0;  // 任务5：交付的半个圆形ore数量
    bool task5Started = false;  // 任务5是否开始
    int task5TimeLimit = 2 * 60 * 1000;  // 任务5时间限制（5分钟）
    QTimer task5Timer;  // 任务5计时器

    int gold_ = 0;  // 金币数量
    storescene storescene_;  // 商店界面


    void showUpgradeDialog(const QString &message);

    bool hasAddedDeliveryCenter = false;  // 是否已经添加过交付中心
    bool hasAddedSource = false;  // 是否已经添加过矿井
    bool hasAddedMultiplier = false;
    bool hasBoughtMultiplier = false;

    bool task1completed = 0;
    bool task2completed = 0;
    bool task3completed = 0;
    bool task4completed = 0;
    bool task5completed = 0;
    bool task5lost = 0;

    void saveGameProgress();

};

#endif // GAMESCENE_H
