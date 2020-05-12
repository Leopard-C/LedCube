#pragma once
#include <ostream>
#include "./enum.h"

/*******************  Coordinate ********************/
struct Coordinate {
    Coordinate(int x = 0, int y = 0, int z = 0) :
        x(x), y(y), z(z) {}
    Coordinate getOffset(Direction direction, int val) const {
        switch (direction) {
            case X_ASCEND:  return { x + val, y, z };
            case X_DESCEND: return { x - val, y, z };
            case Y_ASCEND:  return { x, y + val, z };
            case Y_DESCEND: return { x, y - val, z };
            case Z_ASCEND:  return { x, y, z + val };
            case Z_DESCEND: return { x, y, z - val };
            default: return { x, y, z };
        }
    }
    void offset(Direction direction, int val) {
        switch (direction) {
            case X_ASCEND:  x += val;
            case X_DESCEND: x -= val;
            case Y_ASCEND:  y += val;
            case Y_DESCEND: y -= val;
            case Z_ASCEND:  z += val;
            case Z_DESCEND: z -= val;
        }
    }
    bool isValid() const { 
        return x > -1 && x < 8 && y > -1 && y < 8 && z > -1 && z < 8;
    }
    int x;
    int y;
    int z;
};


inline std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
    os << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return os;
}
