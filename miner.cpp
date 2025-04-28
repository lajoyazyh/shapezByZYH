#include "miner.h"
#include "ore.h"
#include <iostream>
#include <QRandomGenerator>
#include <qdebug.h>

using namespace std;

Miner::Miner(double rate, Direction direction, Map* map) : Device(rate), direction_(direction), map_(map), x_(-1), y_(-1) {
    if (map_ == nullptr) {
        qCritical() << "Error: Miner initialized with null map pointer";
        throw std::runtime_error("Miner initialized with null map pointer");
    }
}

void Miner::operate(Map& map, int x, int y) {
    if (map.getCell(x, y).isSource) {
        x_ = x;
        y_ = y;

        // 显式转换 Source::Type 到 Ore::Type
        Ore::Type oreType = static_cast<Ore::Type>(map.getCell(x_, y_).sourceType + 1);
        Ore ore(QRandomGenerator::global()->bounded(5, 15), oreType);  // 生成一个价值在 5 到 14 之间的 Ore

        // 根据方向放置 Ore
        switch (map.getCell(x, y).direction) {
        case EAST:
            if (x_ + 1 < map.getCols() &&
                    (
                        (map.getCell(x_ + 1, y_).deviceType == 3 &&
                                                (map.getCell(x_ + 1, y_).direction == EAST || map.getCell(x_ + 1, y_).direction == WEST_TO_NORTH || map.getCell(x_ + 1, y_).direction == WEST_TO_SOUTH)
                        )|| map.getCell(x_ + 1, y_).isCenter == 1 || map.getCell(x_ + 1, y_).deviceType == 4
                    )
                ) {
                map.placeOre(x_ + 1, y_, oreType, ore.getValue());
                cout << "Ore placed on ConveyorBelt at (" << x_ + 1 << ", " << y_ << ")" << endl;
            }
            break;
        case SOUTH:
            if (y_ + 1 < map.getRows() &&
                    (
                        (map.getCell(x_, y_ + 1).deviceType == 3 &&
                                (map.getCell(x_, y_ + 1).direction == SOUTH || map.getCell(x_, y_ + 1).direction == NORTH_TO_EAST || map.getCell(x_, y_ + 1).direction == NORTH_TO_WEST)
                        ) || map.getCell(x_, y_ + 1).isCenter == 1 || map.getCell(x_, y_ + 1).deviceType == 4
                    )
                ) {
                map.placeOre(x_, y_ + 1, oreType, ore.getValue());
                cout << "Ore placed on ConveyorBelt at (" << x_ << ", " << y_ + 1 << ")" << endl;
            }
            break;
        case WEST:
            if (x_ - 1 >= 0 &&
                    (
                        (map.getCell(x_ - 1, y_).deviceType == 3 &&
                                (map.getCell(x_ - 1, y_).direction == WEST || map.getCell(x_ - 1, y_).direction == EAST_TO_NORTH || map.getCell(x_ - 1, y_).direction == EAST_TO_SOUTH)
                        ) || map.getCell(x_ - 1, y_).isCenter == 1 || map.getCell(x_ - 1, y_).deviceType == 4
                    )
                ) {
                map.placeOre(x_ - 1, y_, oreType, ore.getValue());
                cout << "Ore placed on ConveyorBelt at (" << x_ - 1 << ", " << y_ << ")" << endl;
            }
            break;
        case NORTH:
            if (y_ - 1 >= 0 &&
                    (
                        (map.getCell(x_, y_ - 1).deviceType == 3 &&
                                (map.getCell(x_, y_ - 1).direction == NORTH || map.getCell(x_, y_ - 1).direction == SOUTH_TO_EAST || map.getCell(x_, y_ - 1).direction == SOUTH_TO_WEST)
                        ) || map.getCell(x_, y_ - 1).isCenter == 1 || map.getCell(x_, y_ - 1).deviceType == 4
                    )
                ) {
                map.placeOre(x_, y_ - 1, oreType, ore.getValue());
                cout << "Ore placed on ConveyorBelt at (" << x_ << ", " << y_ - 1 << ")" << endl;
            }
            break;
        default:
            break;
        }
    }
}
