#include "device.h"

Device::Device(double rate) : rate_(rate) {}

double Device::getRate() const {
    return rate_;
}

void Device::setRate(double rate) {
    rate_ = rate;
}
