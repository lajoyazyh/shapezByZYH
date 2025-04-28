#ifndef ORE_H
#define ORE_H

class Ore {
public:
    enum Type {
        none,
        SQUARE_ORE,
        CIRCLE_ORE,
        SQUARE_ORE_CUT_VERTICAL,
        SQUARE_ORE_CUT_HORIZONTAL,
        CIRCLE_ORE_CUT_VERTICAL,
        CIRCLE_ORE_CUT_HORIZONTAL
    };

    // 构造函数声明，包含两个参数：价值和类型
    Ore(int value, Type type);

    // 获取矿物的价值
    int getValue() const;

    // 获取矿物的类型
    Type getType() const;

private:
    int value_; // 开采矿物的价值
    Type type_; // 开采矿物的类型
};

#endif // ORE_H
