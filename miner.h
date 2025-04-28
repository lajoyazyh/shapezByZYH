#ifndef MINER_H
#define MINER_H

#include "device.h"
#include "map.h"
#include "directions.h"
#include "ore.h"

class Miner : public Device {
public:
    explicit Miner(double rate, Direction direction = EAST, Map* map = nullptr);
    void operate(Map& map, int x, int y) override;
    void setDirection(Direction direction) { direction_ = direction; }
    Direction getDirection() const { return direction_; }

private:
    Direction direction_;  // 开采器方向
    Map* map_;  // 指向 Map 对象的指针
    int x_;  // 当前位置的 x 坐标
    int y_;  // 当前位置的 y 坐标
};

#endif // MINER_H
