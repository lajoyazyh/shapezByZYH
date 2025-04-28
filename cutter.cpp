#include "cutter.h"
#include <iostream>
#include "ore.h"
#include "ore_cut.h"

using namespace std;

Cutter::Cutter(double rate, Direction direction) : Device(rate), direction_(direction) {}

void Cutter::operate(Map& map, int x, int y) {
    cout << "Cutter is operating with rate " << getRate() << " and direction " << static_cast<int>(direction_) << endl;

    // 检查当前位置是否有物品且未被移动
    if (map.getCell(x, y).oreType > 0 && !map.getCell(x, y).isMoved) {
        // 根据方向处理开采物
        int oreType = map.getCell(x, y).oreType;
        int oreValue = map.getCell(x, y).oreValue;

        // 定义两个输出位置
        int targetX1 = x, targetY1 = y;
        int targetX2 = x, targetY2 = y;

        int direction_ = map.getCell(x, y).direction;

        // 根据方向设置两个输出位置
        switch (direction_) {
        case NORTH:
            targetY1 = y - 1;
            targetX2 = x + 1;
            targetY2 = y - 1;
            break;
        case EAST:
            targetX1 = x + 1;
            targetX2 = x + 1;
            targetY2 = y + 1;
            break;
        case SOUTH:
            targetY1 = y + 1;
            targetX2 = x - 1;
            targetY2 = y + 1;
            break;
        case WEST:
            targetX1 = x - 1;
            targetX2 = x - 1;
            targetY2 = y - 1;
            break;
        default:
            break;
        }

        // 检查两个输出位置是否有效且连接了合适的设备
        bool validOutput1 = isValidOutput(map, targetX1, targetY1);
        bool validOutput2 = isValidOutput(map, targetX2, targetY2);

        if (validOutput1 && validOutput2) {
            // 根据矿石类型和方向进行切割
            switch (oreType) {
            case Ore::SQUARE_ORE:
                if (direction_ == NORTH || direction_ == SOUTH) {
                    map.placeOre(targetX1, targetY1, Ore::SQUARE_ORE_CUT_VERTICAL, oreValue);
                    map.placeOre(targetX2, targetY2, Ore::SQUARE_ORE_CUT_VERTICAL, oreValue);
                } else {
                    map.placeOre(targetX1, targetY1, Ore::SQUARE_ORE_CUT_HORIZONTAL, oreValue);
                    map.placeOre(targetX2, targetY2, Ore::SQUARE_ORE_CUT_HORIZONTAL, oreValue);
                }
                break;
            case Ore::CIRCLE_ORE:
                if (direction_ == NORTH || direction_ == SOUTH) {
                    map.placeOre(targetX1, targetY1, Ore::CIRCLE_ORE_CUT_VERTICAL, oreValue);
                    map.placeOre(targetX2, targetY2, Ore::CIRCLE_ORE_CUT_VERTICAL, oreValue);
                } else {
                    map.placeOre(targetX1, targetY1, Ore::CIRCLE_ORE_CUT_HORIZONTAL, oreValue);
                    map.placeOre(targetX2, targetY2, Ore::CIRCLE_ORE_CUT_HORIZONTAL, oreValue);
                }
                break;
            default:
                break;
            }

            // 清空当前位置的物品
            map.placeOre(x, y, 0, 0);
            // 标记目标位置的物品已移动
            map.setMovedFlag(targetX1, targetY1, true);
            map.setMovedFlag(targetX2, targetY2, true);
            cout << "Ore cut and moved to Cutter outputs at (" << targetX1 << ", " << targetY1 << ") and (" << targetX2 << ", " << targetY2 << ")" << endl;
        }
    }
}

bool Cutter::isValidOutput(Map& map, int x, int y) {
    if (x < 0 || x >= map.getCols() || y < 0 || y >= map.getRows()) {
        return false;  // 位置无效
    }
    int deviceType = map.getCell(x, y).deviceType;
    return deviceType == 1 || deviceType ==  3 || deviceType == 5 || map.getCell(x, y).isCenter;  // 3 表示 ConveyorBelt, 5 表示 TrashBin
}
