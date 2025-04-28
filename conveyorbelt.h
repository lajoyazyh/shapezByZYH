#ifndef CONVEYORBELT_H
#define CONVEYORBELT_H

#include "device.h"
#include "map.h"
#include "directions.h"

class ConveyorBelt : public Device {
public:
    explicit ConveyorBelt(double rate, Direction direction = EAST);
    void operate(Map& map, int x, int y) override;
    void setDirection(Direction direction) { direction_ = direction; }
    Direction getDirection() const { return direction_; }

private:
    Direction direction_;  // 传送带方向
};

#endif // CONVEYORBELT_H
