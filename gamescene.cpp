#include "gamescene.h"
#include "ui_gamescene.h"
#include <QPen>
#include <QPoint>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <iostream>
#include "source.h"
#include "map.h"
#include "miner.h"
#include "conveyorbelt.h"
#include "cutter.h"
#include "trashbin.h"
#include <QPixmap>
#include <QTimer>
#include <cmath>
#include "upgradedialog.h"
#include <QMessageBox>
#include <QFileDialog>  // 用于文件选择对话框
#include <QMessageBox>  // 用于显示消息框
#include <QFile>        // 用于文件操作
#include <QDataStream>  // 用于数据流操作
#include <QIODevice>    // 用于设备操作

using namespace std;

gamescene::gamescene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamescene)
    , map(12, 20)  // 初始化 Map 为 11x20
    , miner(0.5, EAST, &map)  // 初始化 Miner 速率
    , conveyorBelt(1.0, EAST)  // 初始化 ConveyorBelt 速率
    , cutter(0.5, EAST)  // 初始化 Cutter 速率
    , trashBin(10.0)  // 初始化 TrashBin 速率
    , selectedDeviceType(0)  // 当前选中的设备类型
    , selectedDirection(EAST)  // 当前选中的设备方向，默认东
    , storescene_(this)  // 初始化商店界面
{
    ui->setupUi(this);
    setFixedSize(1000, 900);

    // 连接商店按钮
    connect(ui->pushButtonShop, &QPushButton::clicked, this, &gamescene::on_pushButtonShop_clicked);


    // 加载图片素材
    QPixmap blockPic(":/images/resource/images/block.png");
    QPixmap sourcePic1(":/images/resource/images/rectangle.png");
    QPixmap sourcePic2(":/images/resource/images/circle.png");
    QPixmap deliveryCenterPic(":/images/resource/images/delivery_center.png");
    QPixmap minerPic(":/images/resource/images/miner.png");
    QPixmap conveyorBeltPic(":/images/resource/images/conveyor_belt.png");
    QPixmap cutterPic(":/images/resource/images/cutter.png");
    QPixmap trashBinPic(":/images/resource/images/trash_bin.png");
    QPixmap multiplierPic(":/images/resource/images/mutiplier.png");

    // 初始化地图
    map.setDeliveryCenter(7, 3, 2, 3);

    // 假设 blockPic, sourcePic1, sourcePic2 已经被正确加载

    // 放置方形矿井
    map.placeSource(3, 1, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(4, 1, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(3, 2, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(4, 2, sourcePic1, Source::SQUARE_ORE);  // 方形矿井

    map.placeSource(2, 7, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(2, 8, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(3, 9, sourcePic1, Source::SQUARE_ORE);  // 方形矿井

    map.placeSource(14, 5, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(14, 6, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(14, 7, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(15, 6, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(15, 7, sourcePic1, Source::SQUARE_ORE);  // 方形矿井

    map.placeSource(18,9, sourcePic1, Source::SQUARE_ORE);  // 方形矿井
    map.placeSource(18,7, sourcePic1, Source::SQUARE_ORE);  // 方形矿井

    // 放置圆形矿井
    map.placeSource(1, 9, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(1, 10, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(2, 9, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(2, 10, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(5, 9, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(17, 0, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(17, 3, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(18, 6, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井
    map.placeSource(15, 4, sourcePic2, Source::CIRCLE_ORE);  // 圆形矿井

    // 随机放置障碍物，确保不与矿井和交易中心重合
    map.placeBlock(2, 4, blockPic);
    map.placeBlock(6, 3, blockPic);
    map.placeBlock(3, 7, blockPic);
    map.placeBlock(6, 2, blockPic);
    map.placeBlock(7, 2, blockPic);
    map.placeBlock(3, 8, blockPic);
    map.placeBlock(11, 5, blockPic);
    map.placeBlock(13, 8, blockPic);
    map.placeBlock(14, 4, blockPic);
    map.placeBlock(14, 3, blockPic);
    map.placeBlock(14, 10, blockPic);
    map.placeBlock(16, 2, blockPic);
    map.placeBlock(18, 7, blockPic);
    map.placeBlock(19, 9, blockPic);




    // 启动整体更新定时器
    timer.setInterval((1.0 / conveyorBelt.getRate()) * 1000);
    connect(&timer, &QTimer::timeout, this, &gamescene::updateGame);
    timer.start();

    // 启动 Miner 更新定时器
    minerTimer.setInterval((1.0 / miner.getRate()) * 1000);
    connect(&minerTimer, &QTimer::timeout, this, &gamescene::updateMiner);
    minerTimer.start();

    // 启动 Cutter 更新定时器
    cutterTimer.setInterval(1.0 / (cutter.getRate()) * 1000);
    connect(&cutterTimer, &QTimer::timeout, this, &gamescene::updateCutter);
    cutterTimer.start();

    // 启动 TrashBin 更新定时器
    trashBinTimer.setInterval(1.0 / (trashBin.getRate()) * 1000);
    connect(&trashBinTimer, &QTimer::timeout, this, &gamescene::updateTrashBin);
    trashBinTimer.start();

    connect(ui->pushButtonTask5, &QPushButton::clicked, this, &gamescene::on_pushButtonTask5_clicked);

    // 连接商店按钮
    connect(ui->pushButtonShop, &QPushButton::clicked, this, &gamescene::on_pushButtonShop_clicked);

    // 连接商店界面的信号
    connect(&storescene_, &storescene::exchangeOreForGold, this, &gamescene::onExchangeOreForGold);
    connect(&storescene_, &storescene::buyDevice, this, &gamescene::onBuyDevice);
    connect(&storescene_, &storescene::addDeliveryCenter, this, &gamescene::onAddDeliveryCenter);
    connect(&storescene_, &storescene::addSource, this, &gamescene::onAddSource);

}

void gamescene::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // 绘制基础地块
    for (int i = 0; i <= 550; i += 50) {
        painter.drawLine(0, i, 1000, i);
    }
    for (int j = 0; j <= 1000; j += 50) {
        painter.drawLine(j, 0, j, 550);
    }

    // 绘制设备和开采物
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);
            QRect rect(x * 50, y * 50, 50, 50);
            QRect rect_cutter1(x * 50, y * 50, 100, 50);
            QRect rect_cutter2(x * 50, y * 50, 50, 100);
            QRect rect_cutter3((x - 1) * 50, y * 50, 100, 50);
            QRect rect_cutter4(x * 50, (y - 1) * 50, 50, 100);
            QRect rect_ore(x * 50 + 10, y * 50 + 10, 30, 30);
            QRect rect_ore_half_vertical(x * 50 + 17, y * 50 + 10, 15, 30);
            QRect rect_ore_half_horizontal(x * 50, y * 50 + 17, 30, 15);

            // 绘制障碍物
            if (cell.isBlock) {
                painter.drawPixmap(rect, cell.blockPic);
            }

            // 绘制矿井
            if (cell.isSource) {
                if (cell.sourceType == Source::SQUARE_ORE) {
                    painter.drawPixmap(rect, QPixmap(":/images/resource/images/source_square.png"));
                } else {
                    painter.drawPixmap(rect, QPixmap(":/images/resource/images/source_circle.png"));
                }
            }

            // 绘制交付中心
            if (cell.isCenter) {
                if(cell.isMultiplier == true){
                    painter.drawPixmap(rect, QPixmap(":/images/resource/images/mutiplier.png"));
                }else{
                    painter.drawPixmap(rect, QPixmap(":/images/resource/images/center1.png"));
                }
            }

            // 绘制设备
            if (cell.deviceType > 0) {
                switch (cell.deviceType) {
                case 2:  // Miner
                    switch (cell.direction) {
                    case NORTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/miner_north.png"));
                        break;
                    case EAST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/miner_east.png"));
                        break;
                    case SOUTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/miner_south.png"));
                        break;
                    case WEST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/miner_west.png"));
                        break;
                    }
                    break;
                case 3:  // ConveyorBelt
                    switch (cell.direction) {
                    case NORTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_north.png"));
                        break;
                    case EAST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_east.png"));
                        break;
                    case SOUTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_south.png"));
                        break;
                    case WEST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_west.png"));
                        break;
                    case NORTH_TO_EAST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_north_east.png"));
                        break;
                    case SOUTH_TO_EAST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_south_east.png"));
                        break;
                    case SOUTH_TO_WEST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_south_west.png"));
                        break;
                    case NORTH_TO_WEST:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_north_west.png"));
                        break;
                    case EAST_TO_NORTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_east_north.png"));
                        break;
                    case EAST_TO_SOUTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_east_south.png"));
                        break;
                    case WEST_TO_SOUTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_west_south.png"));
                        break;
                    case WEST_TO_NORTH:
                        painter.drawPixmap(rect, QPixmap(":/images/resource/images/conveyor_belt_west_north.png"));
                        break;
                    }
                    break;
                case 4:  // 切割机
                    switch (cell.direction) {
                    case NORTH:
                        painter.drawPixmap(rect_cutter1, QPixmap(":/images/resource/images/cut_north.png"));
                        break;
                    case EAST:
                        painter.drawPixmap(rect_cutter2, QPixmap(":/images/resource/images/cut_east.png"));
                        break;
                    case SOUTH:
                        painter.drawPixmap(rect_cutter3, QPixmap(":/images/resource/images/cut_south.png"));
                        break;
                    case WEST:
                        painter.drawPixmap(rect_cutter4, QPixmap(":/images/resource/images/cut_west.png"));
                        break;
                    }
                    break;
                case 5:  // TrashBin
                    painter.drawPixmap(rect, QPixmap(":/images/resource/images/trash_bin.png"));
                    break;
                // case 6:
                //     painter.drawPixmap(rect, QPixmap(":/images/resource/images/mutiplier.png"));
                //     break;
                }
            }

            // 绘制开采物
            if (cell.oreType > 0) {
                QPixmap orePic;
                switch (cell.oreType) {
                case Ore::SQUARE_ORE:
                    orePic = QPixmap(":/images/resource/images/ore_square.png");
                    painter.drawPixmap(rect_ore, orePic);
                    break;
                case Ore::CIRCLE_ORE:
                    orePic = QPixmap(":/images/resource/images/ore_circle.png");
                    painter.drawPixmap(rect_ore, orePic);
                    break;
                case Ore::SQUARE_ORE_CUT_VERTICAL:
                    orePic = QPixmap(":/images/resource/images/ore_square_cut_vertical.png");
                    painter.drawPixmap(rect_ore_half_vertical, orePic);
                    break;
                case Ore::SQUARE_ORE_CUT_HORIZONTAL:
                    orePic = QPixmap(":/images/resource/images/ore_square_cut_horizontal.png");
                    painter.drawPixmap(rect_ore_half_horizontal, orePic);
                    break;
                case Ore::CIRCLE_ORE_CUT_VERTICAL:
                    orePic = QPixmap(":/images/resource/images/ore_circle_cut_vertical.png");
                    painter.drawPixmap(rect_ore_half_vertical, orePic);
                    break;
                case Ore::CIRCLE_ORE_CUT_HORIZONTAL:
                    orePic = QPixmap(":/images/resource/images/ore_circle_cut_horizontal.png");
                    painter.drawPixmap(rect_ore_half_horizontal, orePic);
                    break;
                default:
                    break;
                }


                cout << "ore " << cell.oreType << " drawn\n";
                // painter.drawText(rect, Qt::AlignCenter, QString::number(cell.oreValue));
            }
        }
    }


    // 绘制矿物数量和任务完成情况
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12, QFont::Bold));

    // 绘制方形矿物数量
    painter.drawText(10, 690, QString("Square Ores: %1").arg(squareOreCount));

    // 绘制圆形矿物数量
    painter.drawText(10, 710, QString("Circle Ores: %1").arg(circleOreCount));

    // 绘制半个方形矿物数量
    painter.drawText(200, 690, QString("Half Square Ores: %1").arg(halfSquareOreCount));

    // 绘制半个圆形矿物数量
    painter.drawText(200, 710, QString("Half Circle Ores: %1").arg(halfCircleOreCount));

    // 绘制任务完成情况
    if (task1completed) {
        painter.drawText(10, 730, "Task 1 completed: 20 square ores delivered.");
    } else {
        painter.drawText(10, 730, QString("Task 1: %1/20 square ores delivered").arg(squareOreCount));
    }

    if (task2completed) {
        painter.drawText(10, 750, "Task 2 completed: 30 circle ores delivered.");
    } else {
        painter.drawText(10, 750, QString("Task 2: %1/30 circle ores delivered").arg(circleOreCount));
    }

    // 绘制任务3完成情况
    if (task3completed) {
        painter.drawText(10, 770, "Task 3 completed: 50 half square ores delivered.");
    } else {
        painter.drawText(10, 770, QString("Task 3: %1/50 half square ores delivered").arg(halfSquareOreCount));
    }

    // 绘制任务4完成情况
    if (task4completed) {
        painter.drawText(10, 790, "Task 4 completed: 10 circle ores and 20 half circle ores delivered.");
    } else {
        painter.drawText(10, 790, QString("Task 4: %1/10 circle ores and %2/20 half circle ores delivered").arg(circleOreCount).arg(halfCircleOreCount));
    }

    // 绘制任务5开始提示和具体要求
    if (task5Started) {
        if(task5lost == 1){
            painter.drawText(10, 820, "Task 5 failed! We have taken all the ores you have as a penalty!");
        }else if (task5completed == 1){
            painter.drawText(10, 820, "Task 5 completed!");
        }else{
            painter.drawText(10, 820, "Task 5 started. You have 2 minutes to complete it.   Task 5 requirements:");
            painter.drawText(10, 840, QString("1. Deliver %1/20 square ores 2. Deliver %2/30 circle ores").arg(task5SquareOreCount).arg(task5CircleOreCount));
            painter.drawText(10, 860, QString("3. Deliver %1/50 half square ores 4. Deliver %2/25 half circle ores").arg(task5HalfSquareOreCount).arg(task5HalfCircleOreCount));
            painter.drawText(10, 880, "Time left: " + QString::number(task5Timer.remainingTime() / 1000) + " seconds");
        }

    } else {
        painter.drawText(10, 870, "Click 'Start Task 5' to begin the challenge.");
    }

}

void gamescene::mouseReleaseEvent(QMouseEvent *event)
{
    // 释放鼠标时不做额外处理
}

void gamescene::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x() / 50;
    int y = event->pos().y() / 50;
    const Cell& cell = map.getCell(x, y);

    if (event->button() == Qt::LeftButton && selectedDeviceType > 0 && selectedDeviceType < 6) {
        if (map.canPlaceDevice(x, y, selectedDeviceType, selectedDirection)) {
            map.placeDevice(x, y, selectedDeviceType, selectedDirection);
            update();  // 重新绘制窗口
        }
    }else if (event->button() == Qt::LeftButton && selectedDeviceType == 6) {
        if (map.getCell(x, y).isCenter) {
            map.setMultiplierFlag(x, y, true);
            selectedDeviceType = 0;  // 重置选中的设备类型
            update();  // 重新绘制窗口
        } else {
            QMessageBox::warning(this, "Placement", "You can only place the Multiplier on a Delivery Center.");
        }
    } else if (event->button() == Qt::RightButton) {
        if (cell.deviceType > 0 && !cell.isBlock && !cell.isCenter && !cell.isSource) {
            // 创建一个表示空格子的 Cell 对象
            Cell emptyCell(0, EAST, 0, 0, false, false, false, false, Source::SQUARE_ORE, QPixmap(), QPixmap(), QPixmap(), QPixmap(), QPixmap(), QPixmap(), QPixmap());
            map.setCell(x, y, emptyCell);  // 清除当前格子的设备
            if (cell.deviceType == 4) {  // Cutter
                switch (cell.direction) {
                case EAST:
                    map.setCell(x + 1, y, emptyCell);
                    break;
                case SOUTH:
                    map.setCell(x, y + 1, emptyCell);
                    break;
                case WEST:
                    map.setCell(x - 1, y, emptyCell);
                    break;
                case NORTH:
                    map.setCell(x, y - 1, emptyCell);
                    break;
                default:
                    break;
                }
            }
            update();  // 重新绘制窗口
        }
    }
}

void gamescene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S) {
        // 顺时针旋转方向
        if (selectedDeviceType == 3) {  // 传送带有12个方向
            selectedDirection = static_cast<Direction>((static_cast<int>(selectedDirection) + 1) % 12);
        } else {  // 其他设备有4个方向
            selectedDirection = static_cast<Direction>((static_cast<int>(selectedDirection) + 1) % 4);
        }
        update();  // 重新绘制窗口
    } else if (event->key() == Qt::Key_W) {
        // 逆时针旋转方向
        if (selectedDeviceType == 3) {  // 传送带有12个方向
            selectedDirection = static_cast<Direction>((static_cast<int>(selectedDirection) + 11) % 12);
        } else {  // 其他设备有4个方向
            selectedDirection = static_cast<Direction>((static_cast<int>(selectedDirection) + 3) % 4);
        }
        update();  // 重新绘制窗口
    }
}

void gamescene::on_pushButtonMiner_clicked()
{
    selectedDeviceType = 2;  // 选中开采器
    selectedDirection = EAST;  // 重置方向为东
}

void gamescene::on_pushButtonConveyorBelt_clicked()
{
    selectedDeviceType = 3;  // 选中传送带
    selectedDirection = EAST;  // 重置方向为东
}

void gamescene::on_pushButtonTrashBin_clicked()
{
    selectedDeviceType = 5;  // 选中垃圾桶
    selectedDirection = EAST;  // 重置方向为东
}

void gamescene::on_pushButtonCutter_clicked()
{
    selectedDeviceType = 4;  // 选中切割机
    selectedDirection = EAST;  // 重置方向为东
}

void gamescene::updateMiner() {
    // 遍历地图，调用每个 Miner 的 operate 方法
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);
            if (cell.deviceType == 2) {  // 2 表示 Miner
                miner.operate(map, x, y);
            }
        }
    }
}


void gamescene::updateCutter() {
    // 遍历地图，调用每个 Cutter 的 operate 方法
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);
            if (cell.deviceType == 4) {  // 4 表示 Cutter
                cutter.operate(map, x, y);
            }
        }
    }
}

void gamescene::updateTrashBin() {
    // 遍历地图，调用每个 TrashBin 的 operate 方法
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);
            if (cell.deviceType == 5) {  // 5 表示 TrashBin
                trashBin.operate(map, x, y);
                update();
            }
        }
    }
}

void gamescene::updateGame() {

    // 遍历地图，调用每个 ConveyorBelt 的 operate 方法
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);
            if (cell.deviceType == 3) {  // 3 表示 ConveyorBelt
                conveyorBelt.operate(map, x, y);
            }
        }
    }

    // 检查是否有 Ore 传送到交付中心
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);

            if (cell.isCenter && cell.oreType > 0) {
                // 根据 Ore 类型计数
                if (cell.oreType == Ore::SQUARE_ORE) {
                    squareOreCount++;
                    if (cell.isMultiplier) squareOreCount++;
                    if (task5Started && !task5completed) task5SquareOreCount++;
                } else if (cell.oreType == Ore::CIRCLE_ORE) {
                    circleOreCount++;
                    if (cell.isMultiplier) circleOreCount++;
                    if (task5Started && !task5completed) task5CircleOreCount++;
                }else if (cell.oreType == Ore::SQUARE_ORE_CUT_VERTICAL || cell.oreType == Ore::SQUARE_ORE_CUT_HORIZONTAL) {
                    halfSquareOreCount++;
                    if (cell.isMultiplier) halfSquareOreCount++;
                    if (task5Started && !task5completed) task5HalfSquareOreCount++;
                } else if (cell.oreType == Ore::CIRCLE_ORE_CUT_VERTICAL || cell.oreType == Ore::CIRCLE_ORE_CUT_HORIZONTAL) {
                    halfCircleOreCount++;
                    if (cell.isMultiplier) halfCircleOreCount++;
                    if (task5Started && !task5completed) task5HalfCircleOreCount++;
                }

                if (squareOreCount >= 20 && task1completed == 0) {
                    // 任务1完成
                    qDebug() << "Task 1 completed: 20 square ores delivered.";
                    showUpgradeDialog("Task 1 completed: 20 square ores delivered.");
                    task1completed = 1;
                }

                if (circleOreCount >= 30 && task2completed == 0) {
                    // 任务2完成
                    qDebug() << "Task 2 completed: 30 circle ores delivered.";
                    showUpgradeDialog("Task 2 completed: 30 circle ores delivered.");
                    task2completed = 1;
                }

                if (halfSquareOreCount >= 50 && task3completed == 0) {
                    qDebug() << "Task 3 completed: 50 half square ores delivered.";
                    showUpgradeDialog("Task 3 completed: 50 half square ores delivered.");
                    task3completed = 1;
                }

                if ((circleOreCount >= 10 && halfCircleOreCount >= 20) && task4completed == 0) {
                    qDebug() << "Task 4 completed: 10 circle ores and 20 half circle ores delivered.";
                    showUpgradeDialog("Task 4 completed: 10 circle ores and 20 half circle ores delivered.");
                    task4completed = 1;
                }

                // 检查任务5是否完成
                if (task5SquareOreCount >= 20 && task5CircleOreCount >= 30 && task5HalfSquareOreCount >= 50 && task5HalfCircleOreCount >= 25 && task5completed == 0) {
                    task5completed = true;
                    qDebug() << "Task 5 completed: 20 square ores and 30 circle ores and 50 half square ores and 25 half circle ores delivered.";
                    showUpgradeDialog("Task 5 completed: 20 square ores and 30 circle ores and 50 half square ores and 25 half circle ores delivered.");
                }

                // 清除交付中心的 Ore，保留交付中心的其他属性
                Cell centerCell = map.getCell(x, y);
                centerCell.oreType = 0;
                centerCell.oreValue = 0;
                map.setCell(x, y, centerCell);
            }
        }
    }

    // 重置所有格子的 isMoved 标记
    map.resetMovedFlags();

    // 重新绘制界面
    update();
}

void gamescene::on_pushButtonTask5_clicked()
{
    if (!task5Started) {
        task5Started = true;
        task5Timer.setSingleShot(true);
        task5Timer.setInterval(task5TimeLimit);
        connect(&task5Timer, &QTimer::timeout, this, &gamescene::checkTask5Completion);
        task5Timer.start();
        qDebug() << "Task 5 started. You have 2 minutes to complete it.";
    } else {
        qDebug() << "Task 5 is already started.";
    }
}

void gamescene::checkTask5Completion() {
    if (squareOreCount >= 20 && circleOreCount >= 30 && halfSquareOreCount >= 50 && halfCircleOreCount >= 25) {
        task5completed = true;
        //qDebug() << "Task 5 completed within time limit!";

    } else {
        clearOres();  // 清空所有开采物
        qDebug() << "Time limit reached, Task 5 not completed. All ores are cleared as a penalty.";
        task5lost = 1;
    }
}

void gamescene::startTask5Timer() {
    if (!task5Started) {
        task5Started = true;
        task5SquareOreCount = 0;
        task5CircleOreCount = 0;
        task5HalfSquareOreCount = 0;
        task5HalfCircleOreCount = 0;
        task5Timer.setSingleShot(true);
        task5Timer.setInterval(task5TimeLimit);
        connect(&task5Timer, &QTimer::timeout, this, &gamescene::checkTask5Completion);
        task5Timer.start();
        qDebug() << "Task 5 started. You have 2 minutes to complete it.";
    } else {
        qDebug() << "Task 5 is already started.";
    }
}

void gamescene::showUpgradeDialog(const QString &message) {
    qDebug() << message;
    UpgradeDialog *dialog = new UpgradeDialog(this);
    connect(dialog, &UpgradeDialog::deviceUpgraded, this, [this](const QString &deviceType){
        upgradeDevice(deviceType);
    });
    dialog->exec();
}

void gamescene::upgradeDevice(const QString &deviceType) {
    qDebug() << "Upgrading device:" << deviceType;
    if (deviceType == "ConveyorBelt") {
        conveyorBelt.setRate(conveyorBelt.getRate() * 1.3);  // 提升传送带速率
        qDebug() << "ConveyorBelt upgraded.";
        qDebug() << conveyorBelt.getRate();
        timer.setInterval((1.0 / conveyorBelt.getRate()) * 1000);
    } else if (deviceType == "Miner") {
        miner.setRate(miner.getRate() * 1.3);  // 提升开采器速率
        qDebug() << "Miner upgraded.";
        minerTimer.setInterval((1.0 / miner.getRate()) * 1000);
    } else if (deviceType == "Cutter") {
        cutter.setRate(cutter.getRate() * 1.3);  // 提升切割机速率
        qDebug() << "Cutter upgraded.";
        cutterTimer.setInterval((1.0 / cutter.getRate()) * 1000);
    }
}

gamescene::~gamescene()
{
    delete ui;
}



void gamescene::on_pushButtonShop_clicked()
{
    // 更新商店界面的金币和矿石数量
    storescene_.setGold(gold_);
    storescene_.setOreCounts(squareOreCount, circleOreCount, halfSquareOreCount, halfCircleOreCount);

    storescene_.show();  // 显示商店界面
}

void gamescene::onAddSource()
{
    // 实现添加源头的逻辑
    // 例如，增加一个源头到地图的某个位置
    if (hasAddedSource) {
        QMessageBox::warning(this, "Purchase", "You have already bought this.");
        return;
    }
    if (getGold() >= 100) {
        setGold(getGold() - 100);
        int x = 1;  // 示例位置
        int y = 1;  // 示例位置
        Source::Type type1 = Source::SQUARE_ORE;  // 示例类型
        Source::Type type2 = Source::CIRCLE_ORE;  // 示例类型
        addSource(7, 0, type1);
        addSource(8, 0, type1);
        addSource(9, 0, type1);
        addSource(10, 0, type1);

        addSource(7, 10, type2);
        addSource(8, 10, type2);
        addSource(9, 10, type2);
        addSource(10, 10, type2);

        QMessageBox::information(this, "Purchase", "Bought other sources.");
    } else {
        QMessageBox::warning(this, "Purchase", "Not enough Gold to buy the device.");
    }


}

void gamescene::addSource(int x, int y, Source::Type type)
{
    // 实现添加源头的逻辑
    // 例如，增加一个源头到地图的某个位置
    QPixmap sourcePic;
    if (type == Source::SQUARE_ORE) {
        sourcePic = QPixmap(":/images/resource/images/rectangle.png");
    } else if (type == Source::CIRCLE_ORE) {
        sourcePic = QPixmap(":/images/resource/images/circle.png");
    }
    map.placeSource(x, y, sourcePic, type);
}


void gamescene::onAddDeliveryCenter()
{
    if (hasAddedDeliveryCenter) {
        QMessageBox::warning(this, "Purchase", "You have already bought this.");
        return;
    }

    // 示例位置和尺寸
    int x = 7;
    int y = 3;
    int width = 4;
    int height = 4;
    addDeliveryCenter(x, y, width, height);

    x = 19;
    y = 3;
    width = 1;
    height = 4;
    addDeliveryCenter(x, y, width, height);

    x = 0;
    y = 3;
    width = 1;
    height = 4;
    addDeliveryCenter(x, y, width, height);

    hasAddedDeliveryCenter = true;
}

void gamescene::addDeliveryCenter(int x, int y, int width, int height)
{
    // 调用 Map 类的 setDeliveryCenter 方法来设置交付中心
    map.setDeliveryCenter(x, y, width, height);
}
void gamescene::onBuyDevice()
{
    if (hasAddedMultiplier) {
        QMessageBox::warning(this, "Purchase", "You have already bought this.");
        return;
    }

    if (getGold() < 100) {
        QMessageBox::warning(this, "Purchase", "Not enough Gold to buy the Multiplier.");
        return;
    }

    // 扣除100金币
    setGold(getGold() - 100);

    /// 更新标记
    hasBoughtMultiplier = true;

    // 显示购买成功的消息
    QMessageBox::information(this, "Purchase", "Multiplier added for 100 Gold.");

    // 更新商店界面的金币显示
    storescene_.setGold(getGold());

}

void gamescene::addDevice(int deviceType)
{
    // 实现添加设备的逻辑
    // 例如，增加一个设备到地图的某个位置
    int x = 1;  // 示例位置
    int y = 1;  // 示例位置
    map.placeDevice(x, y, deviceType, EAST);  // 假设设备方向为 EAST
}

void gamescene::onExchangeOreForGold()
{
    // 实现兑换金币的逻辑
    // 例如，一个方形、一个圆形、两个半方、两个半圆合起来换10金币
    // 检查是否有足够的矿石
    if (squareOreCount > 0 && circleOreCount > 0 && halfSquareOreCount >= 2 && halfCircleOreCount >= 2) {
        // 减少矿石数量
        squareOreCount -= 1;
        circleOreCount -= 1;
        halfSquareOreCount -= 2;
        halfCircleOreCount -= 2;

        // 增加金币
        setGold(getGold() + 10);

        // 显示成功信息
        QMessageBox::information(this, "Exchange", "Exchanged 1 Square Ore, 1 Circle Ore, 2 Half Square Ores, and 2 Half Circle Ores for 10 Gold.");
    } else {
        // 显示警告信息
        QMessageBox::warning(this, "Exchange", "Not enough Ores to exchange.");
    }
}

void gamescene::on_pushButton_clicked()
{
    if (!hasBoughtMultiplier) {
        QMessageBox::warning(this, "Purchase", "You need to buy the Multiplier first.");
        return;
    }

    // 允许用户在地图上放置Multiplier设备
    selectedDeviceType = 6;  // 6 表示Multiplier设备
}

void gamescene::clearOres() {
    squareOreCount = 0;
    circleOreCount = 0;
    halfSquareOreCount = 0;
    halfCircleOreCount = 0;
    task5SquareOreCount = 0;
    task5CircleOreCount = 0;
    task5HalfSquareOreCount = 0;
    task5HalfCircleOreCount = 0;
    update();  // 重新绘制界面
}

void gamescene::on_pushButton_2_clicked()
{
    saveGameProgress();
}

void gamescene::saveGameProgress() {
    // 弹出文件保存对话框，让用户选择保存位置
    QString filePath = QFileDialog::getSaveFileName(this, "保存游戏进度", "", "存档文件 (*.dat)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "保存失败", "未选择保存位置。");
        return;
    }

    QFile file(filePath);  // 使用用户选择的文件路径
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "保存失败", "无法打开文件进行写入。");
        return;
    }

    QDataStream out(&file);  // 使用 QDataStream 进行数据写入

    // 保存地图状态
    out << map.getRows();
    out << map.getCols();
    for (int y = 0; y < map.getRows(); ++y) {
        for (int x = 0; x < map.getCols(); ++x) {
            const Cell& cell = map.getCell(x, y);
            out << cell.deviceType;
            out << static_cast<int>(cell.direction);
            out << cell.oreType;
            out << cell.oreValue;
            out << cell.isBlock;
            out << cell.isSource;
            out << cell.isCenter;
            out << cell.isMoved;
            out << cell.isMultiplier;
            out << static_cast<int>(cell.sourceType);
        }
    }

    // 保存资源数量
    out << squareOreCount;
    out << circleOreCount;
    out << halfSquareOreCount;
    out << halfCircleOreCount;

    // 保存任务进度
    out << task1completed;
    out << task2completed;
    out << task3completed;
    out << task4completed;
    out << task5completed;
    out << task5Started;
    out << task5lost;

    // 保存其他需要保存的状态...

    file.close();  // 关闭文件
    QMessageBox::information(this, "保存成功", QString("游戏进度已成功保存到: %1").arg(filePath));
}

void gamescene::loadGameProgress(const QString& filePath) {
    QFile file(filePath);  // 打开存档文件
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "加载失败", "无法打开存档文件。");
        return;
    }

    QDataStream in(&file);

    // 读取地图状态
    int rows, cols;
    in >> rows >> cols;
    map = Map(rows, cols);  // 重新初始化地图
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            Cell cell;
            in >> cell.deviceType;
            int direction;
            in >> direction;
            cell.direction = static_cast<Direction>(direction);
            in >> cell.oreType;
            in >> cell.oreValue;
            in >> cell.isBlock;
            in >> cell.isSource;
            in >> cell.isCenter;
            in >> cell.isMoved;
            in >> cell.isMultiplier;
            int sourceType;
            in >> sourceType;
            cell.sourceType = static_cast<Source::Type>(sourceType);
            map.setCell(x, y, cell);  // 更新地图格子
        }
    }

    // 读取资源数量
    in >> squareOreCount;
    in >> circleOreCount;
    in >> halfSquareOreCount;
    in >> halfCircleOreCount;

    // 读取任务进度
    in >> task1completed;
    in >> task2completed;
    in >> task3completed;
    in >> task4completed;
    in >> task5completed;
    in >> task5Started;
    in >> task5lost;

    file.close();  // 关闭文件
    QMessageBox::information(this, "加载成功", "游戏进度已成功加载。");
    update();  // 重新绘制游戏界面
}
