#include "ore.h"

// 构造函数定义，包含两个参数：价值和类型
Ore::Ore(int value, Ore::Type type) : value_(value), type_(type) {}

// 获取矿物的价值
int Ore::getValue() const {
    return value_;
}

// 获取矿物的类型
Ore::Type Ore::getType() const {
    return type_;
}
