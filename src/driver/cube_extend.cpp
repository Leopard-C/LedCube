#include "cube_extend.h"

extern LedCube cube;

namespace ext {

    
void lightCube(const Vertex& A, const Vertex& B, int fill/* = Fill_Hollow*/) {
    int minX, minY, minZ, maxX, maxY, maxZ;
    if (A.x > B.x) {
        maxX = A.x;
        minX = B.x;
    } else {
        maxX = B.x;
        minX = A.x;
    }

    if (A.y > B.y) {
        maxY = A.y;
        minY = B.y;
    } else {
        maxY = B.y;
        minY = A.y;
    }

    if (A.z > B.z) {
        maxZ = A.z;
        minZ = B.z;
    } else {
        maxZ = B.z;
        minZ = A.z;
    }

    for (int x = minX; x <= maxX; ++x) {
        for (int y = minY; y <= maxY; ++y) {
            for (int z = minZ; z <= maxZ; ++z) {
                cube(x, y, z) = LED_ON;
            }
        }
    }

    if (fill == Fill_Hollow) {
        for (int x = minX + 1; x < maxX; ++x) {
            for (int y = minY + 1; y < maxY; ++y) {
                for (int z = minZ + 1; z < maxZ; ++z) {
                    cube(x, y, z) = LED_OFF;
                }
            }
        }
    }
}


} // namespace ext
