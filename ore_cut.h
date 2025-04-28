#ifndef ORE_CUT_H
#define ORE_CUT_H

#include "ore.h"

class OreCutSquareVertical : public Ore {
public:
    OreCutSquareVertical(int value) : Ore(value, Type::SQUARE_ORE_CUT_VERTICAL) {}
};

class OreCutSquareHorizontal : public Ore {
public:
    OreCutSquareHorizontal(int value) : Ore(value, Type::SQUARE_ORE_CUT_HORIZONTAL) {}
};

class OreCutCircleVertical : public Ore {
public:
    OreCutCircleVertical(int value) : Ore(value, Type::CIRCLE_ORE_CUT_VERTICAL) {}
};

class OreCutCircleHorizontal : public Ore {
public:
    OreCutCircleHorizontal(int value) : Ore(value, Type::CIRCLE_ORE_CUT_HORIZONTAL) {}
};

#endif // ORE_CUT_H
