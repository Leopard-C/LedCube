#include "cube_extend.h"
#include "../utility/ExpressionEvaluator.h"
#include "../utility/image_lib.h"

extern LedCube cube;

namespace ext {

    
void lightCube(const Vertex& A, const Vertex& B, FillType fill) {
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

    if (fill == FILL_EDGE) {
        // parallel to z
        cube.lightRowXY(minX, minY, minZ, maxZ, LED_ON);
        cube.lightRowXY(minX, maxY, minZ, maxZ, LED_ON);
        cube.lightRowXY(maxX, minY, minZ, maxZ, LED_ON);
        cube.lightRowXY(maxX, maxY, minZ, maxZ, LED_ON);
        // parallel to y
        cube.lightRowXZ(minX, minZ, minY + 1, maxY - 1, LED_ON);
        cube.lightRowXZ(minX, maxZ, minY + 1, maxY - 1, LED_ON);
        cube.lightRowXZ(maxX, minZ, minY + 1, maxY - 1, LED_ON);
        cube.lightRowXZ(maxX, maxZ, minY + 1, maxY - 1, LED_ON);
        // parallel to x
        cube.lightRowYZ(minY, minZ, minX + 1, maxX - 1, LED_ON);
        cube.lightRowYZ(minY, maxZ, minX + 1, maxX - 1, LED_ON);
        cube.lightRowYZ(maxY, minZ, minX + 1, maxX - 1, LED_ON);
        cube.lightRowYZ(maxY, maxZ, minX + 1, maxX - 1, LED_ON);
    }
    else if (fill == FILL_SURFACE) {
        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= minY; ++y) {
                cube(x, y, minZ) = LED_ON;
                cube(x, y, maxZ) = LED_ON;
            }
        }
        for (int x = minX; x <= maxX; ++x) {
            for (int z = minZ; z <= maxZ; ++z) {
                cube(x, minY, z) = LED_ON;
                cube(x, maxY, z) = LED_ON;
            }
        }
        for (int y = minY; y <= maxY; ++y) {
            for (int z = minZ; z <= maxZ; ++z) {
                cube(minX, y, z) = LED_ON;
                cube(maxX, y, z) = LED_ON;
            }
        }
    }
    else {
        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= maxY; ++y) {
                for (int z = minZ; z <= maxZ; ++z) {
                    cube(x, y, z) = LED_ON;
                }
            }
        }
    }
}

static void lightSqureInLayerZ(int z, int minX, int maxX, int minY, int maxY, FillType fill) {
    if (fill == FILL_EDGE) {
        for (int x = minX; x <= maxX; ++x) {
            cube(x, minY, z) = LED_ON;
            cube(x, maxY, z) = LED_ON;
        }
        for (int y = minY + 1; y < maxY; ++y) {
            cube(minX, y, z) = LED_ON;
            cube(maxX, y, z) = LED_ON;
        }
    }
    else {
        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= maxY; ++y) {
                cube(x, y, z) = LED_ON;
            }
        }
    }
}

static void lightSqureInLayerY(int y, int minX, int maxX, int minZ, int maxZ, FillType fill) {
    if (fill == FILL_EDGE) {
        for (int x = minX; x <= maxX; ++x) {
            cube(x, y, minZ) = LED_ON;
            cube(x, y, maxZ) = LED_ON;
        }
        for (int z = minZ + 1; z < maxZ; ++z) {
            cube(minX, y, z) = LED_ON;
            cube(maxX, y, z) = LED_ON;
        }
    }
    else {
        for (int x = minX; x <= maxX; ++x) {
            for (int z = minZ; z <= maxZ; ++z) {
                cube(x, y, z) = LED_ON;
            }
        }
    }
}

static void lightSqureInLayerX(int x, int minY, int maxY, int minZ, int maxZ, FillType fill) {
    if (fill == FILL_EDGE) {
        for (int y = minY; y <= maxY; ++y) {
            cube(x, y, minZ) = LED_ON;
            cube(x, y, maxZ) = LED_ON;
        }
        for (int z = minZ + 1; z < maxZ; ++z) {
            cube(x, minY, z) = LED_ON;
            cube(x, maxY, z) = LED_ON;
        }
    }
    else {
        for (int y = minY; y <= maxY; ++y) {
            for (int z = minZ; z <= maxZ; ++z) {
                cube(x, y, z) = LED_ON;
            }
        }
    }
}


void lightSqure(const Vertex& A, const Vertex& B, FillType fill) {
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

    if (A.x == B.x)
        lightSqureInLayerX(A.x, minY, maxY, minZ, maxZ, fill);
    else if (A.y == B.y)
        lightSqureInLayerY(A.y, minX, maxX, minZ, maxZ, fill);
    else if (A.z == B.z)
        lightSqureInLayerZ(A.z, minX, maxX, minY, maxY, fill);
}


void lightCircleInLayerX(int x, int diameter, FillType fill) {
    if (fill == FILL_EDGE) {
        cube.lightLayerX(x, Image_Circle_Edge_1 + diameter - 1, X_ASCEND, ANGLE_0);
    }
    else if (fill == FILL_SOLID || fill == FILL_SURFACE) {
        cube.lightLayerX(x, Image_Circle_Solid_1 + diameter - 1, X_ASCEND, ANGLE_0);
    }
}

void lightCircleInLayerY(int y, int diameter, FillType fill) {
    if (fill == FILL_EDGE) {
        cube.lightLayerY(y, Image_Circle_Edge_1 + diameter - 1, Y_ASCEND, ANGLE_0);
    }
    else if (fill == FILL_SOLID || fill == FILL_SURFACE) {
        cube.lightLayerY(y, Image_Circle_Solid_1 + diameter - 1, Y_ASCEND, ANGLE_0);
    }
}

void lightCircleInLayerZ(int z, int diameter, FillType fill) {
    if (fill == FILL_EDGE) {
        cube.lightLayerZ(z, Image_Circle_Edge_1 + diameter - 1, Z_ASCEND, ANGLE_0);
    }
    else if (fill == FILL_SOLID || fill == FILL_SURFACE) {
        cube.lightLayerZ(z, Image_Circle_Solid_1 + diameter - 1, Z_ASCEND, ANGLE_0);
    }
}


static void replaceAll(std::string& str, const std::string& src, const std::string& des) {
    std::string::size_type pos = 0;
    std::string::size_type srcLen = src.length();
    std::string::size_type desLen = des.length();
    pos = str.find(src, pos);
    while (pos != std::string::npos) {
        str.replace(pos, srcLen, des);
        pos = src.find(src, pos + desLen);
    }
}

static void getValueZ(std::string func, int x, int y, char zArr[]) {
}


void getFrameOfFunction(std::string func, char leds[][8][8]) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            std::string expression = func;
            replaceAll(expression, "x", std::to_string(x));
            replaceAll(expression, "y", std::to_string(y));
            replaceAll(expression, "=", "-(");
            expression += ")";

            std::cout << expression << std::endl;

            ExpressionEvaluator expEv;
            double val;

            for (int z = 0; z < 8; ++z) {
                std::string expTmp = expression;
                replaceAll(expTmp, "z", std::to_string(z));
                val = expEv.eval(expTmp);
                if (val > -0.5 && val < 0.5)
                    cube(x, y, z) = LED_ON;
                    //leds[z][x][y] = LED_ON;
                else
                    cube(x, y, z) = LED_OFF;
                    //leds[z][x][y] = LED_OFF;
            }
        }
    }

    cube.update();
}


} // namespace ext
