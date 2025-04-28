#ifndef TRASHBIN_H
#define TRASHBIN_H

#include "device.h"
#include "map.h"

class TrashBin : public Device {
public:
    explicit TrashBin(double rate);
    void operate(Map& map, int x, int y) override;
};

#endif // TRASHBIN_H
