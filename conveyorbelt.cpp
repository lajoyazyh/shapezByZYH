#include "conveyorbelt.h"
#include <iostream>
#include <QThread>

using namespace std;

ConveyorBelt::ConveyorBelt(double rate, Direction direction) : Device(rate), direction_(direction) {}

void ConveyorBelt::operate(Map& map, int x, int y) {
    cout << "ConveyorBelt is operating with rate " << getRate() << " and direction " << static_cast<int>(map.getCell(x, y).direction) << endl;

    // 定义目标位置
    int targetX = x;
    int targetY = y;

    int oreType = map.getCell(x, y).oreType;

    switch (map.getCell(x, y).direction) {
    case NORTH:
        targetY = y - 1;
        break;
    case EAST:
        targetX = x + 1;
        break;
    case SOUTH:
        targetY = y + 1;
        break;
    case WEST:
        targetX = x - 1;
        break;
    case NORTH_TO_EAST:
        targetX = x + 1;
        break;
    case SOUTH_TO_EAST:
        targetX = x + 1;
        break;
    case SOUTH_TO_WEST:
        targetX = x - 1;
        break;
    case NORTH_TO_WEST:
        targetX = x - 1;
        break;
    case EAST_TO_NORTH:
        targetY = y - 1;
        break;
    case EAST_TO_SOUTH:
        targetY = y + 1;
        break;
    case WEST_TO_SOUTH:
        targetY = y + 1;
        break;
    case WEST_TO_NORTH:
        targetY = y - 1;
        break;
    default:
        break;
    }


    // 检查目标位置是否有效
    int deviceType = map.getCell(targetX, targetY).deviceType;
    int I1 = map.getCell(targetX, targetY).isBlock;
    int I2 = map.getCell(targetX, targetY).isSource;
    int d = map.getCell(x, y).direction;
    int I3 = (d == EAST &&  (map.getCell(x + 1, y).deviceType == 3 &&
                            (map.getCell(x + 1, y).direction == EAST || map.getCell(x + 1, y).direction == WEST_TO_NORTH || map.getCell(x + 1, y).direction == WEST_TO_SOUTH)
                            ))
             || (d == SOUTH &&  (map.getCell(x, y + 1).deviceType == 3 &&
                                (map.getCell(x, y + 1).direction == SOUTH || map.getCell(x, y + 1).direction == NORTH_TO_EAST || map.getCell(x, y + 1).direction == NORTH_TO_WEST)
                                ))
             || (d == WEST &&  (map.getCell(x - 1, y).deviceType == 3 &&
                               (map.getCell(x - 1, y).direction == WEST || map.getCell(x - 1, y).direction == EAST_TO_NORTH || map.getCell(x - 1, y).direction == EAST_TO_SOUTH)
                               ))
             || (d == NORTH &&  (map.getCell(x, y - 1).deviceType == 3 &&
                                (map.getCell(x, y - 1).direction == NORTH || map.getCell(x, y - 1).direction == SOUTH_TO_EAST || map.getCell(x, y - 1).direction == SOUTH_TO_WEST)
                                ))
             || (d == NORTH_TO_EAST &&  (map.getCell(x + 1, y).deviceType == 3 &&
                                (map.getCell(x + 1, y).direction == EAST || map.getCell(x + 1, y).direction == WEST_TO_NORTH || map.getCell(x + 1, y).direction == WEST_TO_SOUTH)
                                ))
             || (d == NORTH_TO_WEST &&  (map.getCell(x - 1, y).deviceType == 3 &&
                                (map.getCell(x - 1, y).direction == WEST || map.getCell(x - 1, y).direction == EAST_TO_NORTH || map.getCell(x - 1, y).direction == EAST_TO_SOUTH)
                                ))
             || (d == SOUTH_TO_EAST &&  (map.getCell(x + 1, y).deviceType == 3 &&
                                (map.getCell(x + 1, y).direction == EAST || map.getCell(x + 1, y).direction == WEST_TO_NORTH || map.getCell(x + 1, y).direction == WEST_TO_SOUTH)
                                ))
             || (d == SOUTH_TO_WEST &&  (map.getCell(x - 1, y).deviceType == 3 &&
                                (map.getCell(x - 1, y).direction == WEST || map.getCell(x - 1, y).direction == EAST_TO_NORTH || map.getCell(x - 1, y).direction == EAST_TO_SOUTH)
                                ))
             || (d == WEST_TO_NORTH &&  (map.getCell(x, y - 1).deviceType == 3 &&
                                (map.getCell(x, y - 1).direction == NORTH || map.getCell(x, y - 1).direction == SOUTH_TO_EAST || map.getCell(x, y - 1).direction == SOUTH_TO_WEST)
                                ))
             || (d == WEST_TO_SOUTH &&  (map.getCell(x, y + 1).deviceType == 3 &&
                                (map.getCell(x, y + 1).direction == SOUTH || map.getCell(x, y + 1).direction == NORTH_TO_WEST || map.getCell(x, y + 1).direction == NORTH_TO_EAST)
                                ))
             || (d == EAST_TO_NORTH &&  (map.getCell(x, y - 1).deviceType == 3 &&
                                (map.getCell(x, y - 1).direction == NORTH || map.getCell(x, y - 1).direction == SOUTH_TO_EAST || map.getCell(x, y - 1).direction == SOUTH_TO_WEST)
                                ))
             || (d == EAST_TO_SOUTH &&  (map.getCell(x, y + 1).deviceType == 3 &&
                                (map.getCell(x, y + 1).direction == SOUTH || map.getCell(x, y + 1).direction == NORTH_TO_WEST || map.getCell(x, y + 1).direction == NORTH_TO_EAST)
                                ))
        ;
    //I3是用来检查传送带接口有没有对齐的

    if (targetX >= 0 && targetX < map.getCols() && targetY >= 0 && targetY < map.getRows() && (deviceType != 0 && deviceType != 2) && !I1 && !I2 && (deviceType != 3 || I3)) {
        // 检查当前位置是否有物品且未被移动,且不能为空格或者采矿机，也不能是障碍或者源头
        if (map.getCell(x, y).oreType > 0 && !map.getCell(x, y).isMoved) {
            // 检查目标位置是否为空
            if (map.getCell(targetX, targetY).oreType == 0) {
                // 移动物品到目标位置
                map.placeOre(targetX, targetY, map.getCell(x, y).oreType, map.getCell(x, y).oreValue);
                // 清空当前位置的物品
                map.placeOre(x, y, 0, 0);
                // 标记目标位置的物品已移动
                map.setMovedFlag(targetX, targetY, true);
                cout << "Ore moved to ConveyorBelt at (" << targetX << ", " << targetY << ")" << endl;
            }
        }
    }
}
