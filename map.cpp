#include "map.h"
#include <iostream>

using namespace std;

Map::Map(int rows, int cols) : rows_(rows), cols_(cols) {
    map_.resize(rows, vector<Cell>(cols));  // 初始化地图，所有格子默认为无设备
}

void Map::setDeliveryCenter(int x, int y, int width, int height) {
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            map_[i][j].deviceType = 1;  // 假设用1表示交付中心
            map_[i][j].isCenter = true;
            map_[i][j].deliveryCenterPic = QPixmap(":/images/resource/images/center1.png");
        }
    }
}

void Map::placeDevice(int x, int y, int deviceType, Direction direction) {
    if (!map_[y][x].isBlock && !(map_[y][x].isSource && deviceType != 2)) {
        map_[y][x].deviceType = deviceType;
        map_[y][x].direction = direction;
        cout << deviceType << "placed\n";
        // switch (deviceType) {
        // case 2:  // 开采器
        //     map_[y][x].minerPic = QPixmap(":/images/resource/images/miner.png");
        //     break;
        // case 3:  // 传送带
        //     map_[y][x].conveyorBeltPic = QPixmap(":/images/resource/images/conveyor_belt.png");
        //     break;
        // case 4:  // 切割机
        //     map_[y][x].cutterPic = QPixmap(":/images/resource/images/cutter.png");
        //     break;
        // case 5:  // 垃圾桶
        //     map_[y][x].trashBinPic = QPixmap(":/images/resource/images/trash_bin.png");
        //     break;
        // default:
        //     break;
        // }
    }
}

void Map::placeBlock(int x, int y, const QPixmap &blockPic) {
    map_[y][x].isBlock = true;
    map_[y][x].blockPic = blockPic;
}

void Map::placeSource(int x, int y, const QPixmap &sourcePic, Source::Type type) {
    map_[y][x].isSource = true;
    map_[y][x].sourcePic = sourcePic;
    map_[y][x].sourceType = type;
}

void Map::placeOre(int x, int y, int oreType, int oreValue) {
    cout << "ore " << oreType << " placed\n";
    map_[y][x].oreType = oreType;
    map_[y][x].oreValue = oreValue;
    map_[y][x].isMoved = true;
}

void Map::printMap() const {
    for (const auto& row : map_) {
        for (const auto& cell : row) {
            cout << "Device: " << cell.deviceType
                 << ", Direction: " << static_cast<int>(cell.direction)
                 << ", OreType: " << cell.oreType
                 << ", OreValue: " << cell.oreValue
                 << ", IsBlock: " << cell.isBlock
                 << ", IsSource: " << cell.isSource
                 << ", IsCenter: " << cell.isCenter
                 << ", SourceType: " << static_cast<int>(cell.sourceType) << " ";
        }
        cout << endl;
    }
}

const Cell& Map::getCell(int x, int y) const {
    if (x < 0 || x >= cols_ || y < 0 || y >= rows_) {
        static Cell invalidCell = {-1, EAST, -1, -1, false, false, false, false, Source::SQUARE_ORE, QPixmap(), QPixmap(), QPixmap(), QPixmap(), QPixmap(), QPixmap(), QPixmap()};
        return invalidCell;
    }
    return map_[y][x];
}

void Map::setCell(int x, int y, const Cell& cell) {
    if (x < 0 || x >= cols_ || y < 0 || y >= rows_) {
        return;  // 位置无效，不进行操作
    }
    map_[y][x] = cell;

}
bool Map::canPlaceDevice(int x, int y, int deviceType, Direction direction) const {
    // 检查当前格子是否可以放置设备
    if ((map_[y][x].deviceType != 0 && map_[y][x].deviceType != deviceType) || map_[y][x].isBlock || map_[y][x].isCenter) {
        return false;
    }

    // 允许在 Source 上放置 Miner
    if (deviceType != 2 && map_[y][x].isSource) {
        return false;
    }

    // 检查 Cutter 占据的第二个格子
    if (deviceType == 4) {  // Cutter
        switch (direction) {
        case EAST:
            if (y + 1 < rows_ && (map_[y + 1][x].deviceType != 0 || map_[y + 1][x].isBlock || map_[y + 1][x].isSource || map_[y + 1][x].isCenter)) {
                return false;
            }
            break;
        case SOUTH:
            if (x - 1 >= 0 && (map_[y][x - 1].deviceType != 0 || map_[y][x - 1].isBlock || map_[y][x - 1].isSource || map_[y][x - 1].isCenter)) {
                return false;
            }
            break;
        case WEST:
            if (y - 1 >= 0 && (map_[y - 1][x].deviceType != 0 || map_[y - 1][x].isBlock || map_[y - 1][x].isSource || map_[y - 1][x].isCenter)) {
                return false;
            }
            break;
        case NORTH:
            if (x + 1 < cols_ && (map_[y][x + 1].deviceType != 0 || map_[y][x + 1].isBlock || map_[y][x + 1].isSource || map_[y][x + 1].isCenter)) {
                return false;
            }
            break;
        default:
            break;
        }
    }

    return true;
}

void Map::resetMovedFlags() {
    for (int y = 0; y < rows_; ++y) {
        for (int x = 0; x < cols_; ++x) {
            map_[y][x].isMoved = false;
        }
    }
}

void Map::setMovedFlag(int x, int y, bool isMoved) {
    if (x < 0 || x >= cols_ || y < 0 || y >= rows_) {
        return;  // 位置无效，不进行操作
    }
    map_[y][x].isMoved = isMoved;
}


void Map::setMultiplierFlag(int x, int y, bool isMultiplier) {
    if (x < 0 || x >= cols_ || y < 0 || y >= rows_) {
        return;  // 位置无效，不进行操作
    }
    map_[y][x].isMultiplier = isMultiplier;
}
