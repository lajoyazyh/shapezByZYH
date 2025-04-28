#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QPixmap>
#include "directions.h"
#include "source.h"

using namespace std;

struct Cell {
    int deviceType = 0;  // 设备类型：0=无设备, 1=交付中心, 2=开采器, 3=传送带, 4=切割机, 5=垃圾桶, 6=Multiplier
    Direction direction = EAST;  // 设备方向
    int oreType = 0;     // 开采矿物类型：0=无开采物, 1=方形矿物, 2=圆形矿物
    int oreValue = 0;    // 开采矿物价值
    bool isBlock = false;  // 是否是障碍物
    bool isSource = false;  // 是否是矿井
    bool isCenter = false;  // 是否为交付中心
    bool isMoved = false;   // 是否已经在一个周期内被传递过
    bool isMultiplier = false;  // 是否被Multiplier设备影响
    Source::Type sourceType = Source::SQUARE_ORE;  // 矿井类型
    QPixmap blockPic;       // 障碍物图片
    QPixmap sourcePic;      // 矿井图片
    QPixmap deliveryCenterPic;  // 交付中心图片
    QPixmap minerPic;       // 开采器图片
    QPixmap conveyorBeltPic;    // 传送带图片
    QPixmap cutterPic;      // 切割机图片
    QPixmap trashBinPic;    // 垃圾桶图片
    QPixmap multiplierPic;  // Multiplier图片

    // 支持初始化列表的构造函数
    Cell(int deviceType = 0, Direction direction = EAST, int oreType = 0, int oreValue = 0, bool isBlock = false, bool isSource = false, bool isCenter = false, bool isMultiplier = false, Source::Type sourceType = Source::SQUARE_ORE, const QPixmap& blockPic = QPixmap(), const QPixmap& sourcePic = QPixmap(), const QPixmap& deliveryCenterPic = QPixmap(), const QPixmap& minerPic = QPixmap(), const QPixmap& conveyorBeltPic = QPixmap(), const QPixmap& cutterPic = QPixmap(), const QPixmap& trashBinPic = QPixmap(), const QPixmap& multiplierPic = QPixmap())
        : deviceType(deviceType), direction(direction), oreType(oreType), oreValue(oreValue), isBlock(isBlock), isSource(isSource), isCenter(isCenter), isMoved(false), sourceType(sourceType), blockPic(blockPic), sourcePic(sourcePic), deliveryCenterPic(deliveryCenterPic), minerPic(minerPic), conveyorBeltPic(conveyorBeltPic), cutterPic(cutterPic), trashBinPic(trashBinPic), multiplierPic(multiplierPic) {}
};

class Map {
public:
    Map(int rows, int cols);
    void setDeliveryCenter(int x, int y, int width, int height);
    void placeDevice(int x, int y, int deviceType, Direction direction = EAST);
    void placeBlock(int x, int y, const QPixmap &blockPic);
    void placeSource(int x, int y, const QPixmap &sourcePic, Source::Type type = Source::SQUARE_ORE);
    void placeOre(int x, int y, int oreType, int oreValue);
    void printMap() const;

    int getRows() const { return rows_; }
    int getCols() const { return cols_; }

    const Cell& getCell(int x, int y) const;
    void setCell(int x, int y, const Cell& cell);
    void setMovedFlag(int x, int y, bool isMoved);  // 新方法，用于更新 isMoved 标记
    void setMultiplierFlag(int x, int y, bool isMultiplier);
    bool canPlaceDevice(int x, int y, int deviceType, Direction direction) const;

    void resetMovedFlags();  // 重置所有格子的 isMoved 标记

private:
    int rows_;
    int cols_;
    vector<vector<Cell>> map_;
};

#endif // MAP_H
