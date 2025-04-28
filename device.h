#ifndef DEVICE_H
#define DEVICE_H

#include "map.h"

class Device {
public:
    Device(double rate);
    virtual ~Device() = default;

    double getRate() const;
    virtual void operate(Map& map, int x, int y) = 0;  // 带参数的虚方法
    void setRate(double rate);  // 声明 setRate 方法

protected:
    double rate_; // 设备速率

};

#endif // DEVICE_H
