#ifndef CUTTER_H
#define CUTTER_H

#include "device.h"
#include "map.h"
#include "directions.h"

class Cutter : public Device {
public:
    explicit Cutter(double rate, Direction direction = EAST);
    void operate(Map& map, int x, int y) override;
    void setDirection(Direction direction) { direction_ = direction; }
    Direction getDirection() const { return direction_; }
    bool isValidOutput(Map& map, int x, int y);

private:
    Direction direction_;  // 切割机方向
};

#endif // CUTTER_H
