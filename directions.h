#ifndef DIRECTIONS_H
#define DIRECTIONS_H

enum Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    NORTH_TO_EAST = 4,  // 拐弯：北到东
    SOUTH_TO_EAST = 5,  // 拐弯：南到东
    SOUTH_TO_WEST = 6,  // 拐弯：南到西
    NORTH_TO_WEST = 7,  // 拐弯：北到西
    EAST_TO_NORTH = 8,  // 拐弯：东到北
    EAST_TO_SOUTH = 9,  // 拐弯：东到南
    WEST_TO_SOUTH = 10,  // 拐弯：西到南
    WEST_TO_NORTH = 11   // 拐弯：西到北
};

#endif // DIRECTIONS_H
