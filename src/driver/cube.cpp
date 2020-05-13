#include "./cube.h"
#include "../utility/image_lib.h"
#include "../utility/utils.h"
#include <cstring>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <wiringPi.h>

LedState LedCube::leds[8][8][8];  // Z X Y
LedState LedCube::ledsBuff[8][8][8];  // Z X Y
int LedCube::vcc[8];
X74hc154 LedCube::x74hc154[4];
bool LedCube::isRunning = true;
bool LedCube::isBackgroundThreadQuit = true;
std::mutex LedCube::mutex_;
bool LedCube::setuped = false;
int LedCube::loopCount = LedCube::DefaultLoopCount;


LedCube::~LedCube() {
    quit();
}

void LedCube::setup() {
    x74hc154[0].setup(17, 27, 22, 5, 6);
    x74hc154[1].setup(17, 27, 22, 5, 13);
    x74hc154[2].setup(17, 27, 22, 5, 19);
    x74hc154[3].setup(17, 27, 22, 5, 26);

    vcc[0] = 18;  vcc[1] = 23;
    vcc[2] = 24;  vcc[3] = 25;
    vcc[4] = 12;  vcc[5] = 16;
    vcc[6] = 20;  vcc[7] = 21;

    for (int i = 0; i < 8; ++i) {
        pinMode(vcc[i], OUTPUT);
    }

    reset();

    std::thread t(backgroundThread);
    t.detach();

    setuped = true;
}

void LedCube::quit() {
    if (setuped) {
        isRunning = false;
        int count = 5;
        while (!isBackgroundThreadQuit && count-- > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        reset();
    }
}

void LedCube::update() {
    mutex_.lock();
    memcpy(leds, ledsBuff, 512);
    mutex_.unlock();
}


void LedCube::reset() {
    // 74hc154
    // set G1 or G2 to HIGH
    // so all the outputs are HIGH
    for (int i = 0; i < 4; ++i) {
        x74hc154[i].enable(false);
    }

    // VCC
    // set all VCC to LOW
    for (int i = 0; i < 8; ++i) {
        digitalWrite(vcc[i], LOW);
    }

    // light off all the LEDs
    for (int z = 0; z < 8; ++z) {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                leds[z][x][y] = LED_OFF;
                ledsBuff[z][x][y] = LED_OFF;
            }
        }
    }

    // set loopCount to default (not zero, see the function)
    setLoopCount(0);
}


/****************************************
 *
 *   Background Thread
 *      scan all of the cube
 *      light on or light off
 *
** *************************************/
void LedCube::backgroundThread() {
    isBackgroundThreadQuit = false;
    while (isRunning) {
        mutex_.lock();
        for (int z = 0; z < 8; ++z) {
            for (int x = 0; x < 8; ++x) {
                int idx = x / 2;
                // power on the layer z
                digitalWrite(vcc[z], HIGH);
                for (int y = 0; y < 8; ++y) {
                    if (leds[z][x][y] == LED_ON) {
                        x74hc154[idx].setOutput(y + 8 * (x % 2));
                        x74hc154[idx].enable(true);
                        // slepp serveral nanoseconds
                        // shouldn't use:
                        //   std::this_thread::sleep_for(std::chrono::nanoseconds(100));
                        //   even if you want to sleep 1 ns, it will consume 10000+ ns really
                        for (int i = 0; i < loopCount; ++i) {
                            //;
                        }
                        x74hc154[idx].enable(false);
                    }
                }
                // power off the layer z
                digitalWrite(vcc[z], LOW);
            }
        }
        mutex_.unlock();
        // delay some time
        //   slepp serveral nanoseconds
        for (int i = 0; i < 5000; ++i) {
            //;
        }
    }

    isBackgroundThreadQuit = true;
    printf("Background thread quit!\n");
}


/************************************
 *
 *   Set all leds to LED_OFF
 *
** **********************************/
void LedCube::clear() {
    memset(ledsBuff, LED_OFF, 512);
}


/**************************************************
 *
 *      Light on or off a layer
 *
**************************************************/
void LedCube::lightLayerZ(int z, LedState state) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            ledsBuff[z][x][y] = state;
        }
    }
}

void LedCube::lightLayerY(int y, LedState state) {
    for (int z = 0; z < 8; ++z) {
        for (int x = 0; x < 8; ++x) {
            ledsBuff[z][x][y] = state;
        }
    }
}

void LedCube::lightLayerX(int x, LedState state) {
    for (int z = 0; z < 8; ++z) {
        for (int y = 0; y < 8; ++y) {
            ledsBuff[z][x][y] = state;
        }
    }
}

void LedCube::lightLayerZ(int z, int imageCode, Direction viewDirection, Angle rotate) {
    Array2D_8_8 image;
    getImageInLayerZ(image, imageCode, viewDirection, rotate);
    lightLayerZ(z, image);
}

void LedCube::lightLayerY(int y, int imageCode, Direction viewDirection, Angle rotate) {
    Array2D_8_8 image;
    getImageInLayerY(image, imageCode, viewDirection, rotate);
    lightLayerY(y, image);
}

void LedCube::lightLayerX(int x, int imageCode, Direction viewDirection, Angle rotate) {
    Array2D_8_8 image;
    getImageInLayerX(image, imageCode, viewDirection, rotate);
    lightLayerX(x, image);
}

void LedCube::lightLayerZ(int z, const Array2D_8_8& image) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            ledsBuff[z][x][y] = image[x][y];
        }
    }
}

void LedCube::lightLayerY(int y, const Array2D_8_8& image) {
    for (int z = 0; z < 8; ++z) {
        for (int x = 0; x < 8; ++x) {
            ledsBuff[z][x][y] = image[z][x];
        }
    }
}

void LedCube::lightLayerX(int x, const Array2D_8_8& image) {
    for (int z = 0; z < 8; ++z) {
        for (int y = 0; y < 8; ++y) {
            ledsBuff[z][x][y] = image[z][y];
        }
    }
}



/***************************************************
 *
 *        Light on or off a row
 *
***************************************************/
// the same state
void LedCube::lightRowXY(int x, int y, LedState state) {
    for (int z = 0; z < 8; ++z) {
        ledsBuff[z][x][y] = state;
    }
}

void LedCube::lightRowYZ(int y, int z, LedState state)  {
    for (int x = 0; x < 8; ++x) {
        ledsBuff[z][x][y] = state;
    }
}

void LedCube::lightRowXZ(int x, int z, LedState state) {
    for (int y = 0; y < 8; ++y) {
        ledsBuff[z][x][y] = state;
    }
}

// the same state
void LedCube::lightRowXY(int x, int y, int zStart, int zEnd, LedState state) {
    for (int z = zStart; z <= zEnd; ++z) {
        ledsBuff[z][x][y] = state;
    }
}

void LedCube::lightRowYZ(int y, int z, int xStart, int xEnd, LedState state) {
    for (int x = xStart; x <= xEnd; ++x) {
        ledsBuff[z][x][y] = state;
    }
}

void LedCube::lightRowXZ(int x, int z, int yStart, int yEnd, LedState state) {
    for (int y = yStart; y <= yEnd; ++y) {
        ledsBuff[z][x][y] = state;
    }
}

// different state
void LedCube::lightRowXY(int x, int y, const std::array<LedState, 8>& state) {
    for (int z = 0; z < 8; ++z) {
        ledsBuff[z][x][y] = state[z];
    }
}

void LedCube::lightRowYZ(int y, int z, const std::array<LedState, 8>& state) {
    for (int x = 0; x < 8; ++x) {
        ledsBuff[z][x][y] = state[x];
    }
}

void LedCube::lightRowXZ(int x, int z, const std::array<LedState, 8>& state) {
    for (int y = 0; y < 8; ++y) {
        ledsBuff[z][x][y] = state[y];
    }
}


/***************************************************
 *
 *      Light a line (3D)
 *
***************************************************/

void LedCube::lightLine(const Coordinate& start, const Coordinate& end, LedState state) {
    std::vector<Coordinate> line;
    util::getLine3D(start, end, line);
    for (auto& point : line) {
        ledsBuff[point.z][point.x][point.y] = state;
    }
}


/***************************************************
 *
 *      Get Image(including text) in a layer
 *
***************************************************/
void LedCube::getImageInLayerZ(Array2D_8_8& image, int imageCode, Direction viewDirection, Angle rotate) {
    auto table = ImageLib::get(imageCode);

    if (viewDirection == Z_DESCEND) {
        switch (rotate) {
        case ANGLE_0:
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    image[x][y] = table[x][y]; 
                }
            }
            break;
        case ANGLE_90:
            for (int y = 7; y > -1; --y) {
                for (int x = 0; x < 8; ++x) {
                    image[x][y] = table[7-y][x];
                }
            }
            break;
        case ANGLE_180:
            for (int x = 7; x > -1; --x) {
                for (int y = 7; y > -1; --y) {
                    image[x][y] = table[7-x][7-y];
                }
            }
            break;
        case ANGLE_270:
            for (int y = 0; y < 8; ++y) {
                for (int x = 7; x > -1; --x) {
                    image[x][y] = table[y][7-x];
                }
            }
            break;
        default:
            break;
        }
    }
    else if (viewDirection == Z_ASCEND) {
        switch (rotate) {
        case ANGLE_0:
            for (int x = 0; x < 8; ++x) {
                for (int y = 7; y > -1; --y) {
                    image[x][y] = table[x][7-y]; 
                }
            }
            break;
        case ANGLE_90:
            for (int y = 0; y < 8; ++y) {
                for (int x = 0; x < 8; ++x) {
                    image[x][y] = table[y][x];
                }
            }
            break;
        case ANGLE_180:
            for (int x = 7; x > -1; --x) {
                for (int y = 0; y < 8; ++y) {
                    image[x][y] = table[7-x][y];
                }
            }
            break;
        case ANGLE_270:
            for (int y = 7; y > -1; --y) {
                for (int x = 7; x > -1; --x) {
                    image[x][y] = table[7-y][7-x];
                }
            }
            break;
        default:
            break;
        }
    }
    else {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                image[x][y] = LED_OFF;
            }
        }
    }
}

void LedCube::getImageInLayerY(Array2D_8_8& image, int imageCode, Direction viewDirection, Angle rotate) {
    auto table = ImageLib::get(imageCode);

    if (viewDirection == Y_DESCEND) {
        switch (rotate) {
        case ANGLE_0:
            for (int z = 7; z > -1; --z) {
                for (int x = 7; x > -1; --x) {
                    image[z][x] = table[7-z][7-x];
                }
            }
            break;
        case ANGLE_90:
            for (int x = 0; x < 8; ++x) {
                for (int z = 7; z > -1; --z) {
                    image[z][x] = table[x][7-z];
                }
            }
            break;
        case ANGLE_180:
            for (int z = 0; z < 8; ++z) {
                for (int x = 0; x < 8; ++x) {
                    image[z][x] = table[z][x];
                }
            }
            break;
        case ANGLE_270:
            for (int x = 7; x > -1; --x) {
                for (int z = 0; z < 8; ++z) {
                    image[z][x] = table[7-x][z];
                }
            }
            break;
        default:
            break;
        }
    }
    else if (viewDirection == Y_ASCEND) {
        switch (rotate) {
        case ANGLE_0:
            for (int z = 7; z > -1; --z) {
                for (int x = 0; x < 8; ++x) {
                    image[z][x] = table[7-z][x];
                }
            }
            break;
        case ANGLE_90:
            for (int x = 7; x > -1; --x) {
                for (int z = 7; z > -1; --z) {
                    image[z][x] = table[7-x][7-z];
                }
            }
            break;
        case ANGLE_180:
            for (int z = 0; z < 8; ++z) {
                for (int x = 7; x > -1; --x) {
                    image[z][x] = table[z][7-x];
                }
            }
            break;
        case ANGLE_270:
            for (int x = 0; x < 8; ++x) {
                for (int z = 0; z < 8; ++z) {
                    image[z][x] = table[x][z];
                }
            }
            break;
        }
    }
    else {
        for (int x = 0; x < 8; ++x) {
            for (int z = 0; z < 8; ++z) {
                image[z][x] = LED_OFF;
            }
        }
    }
}

void LedCube::getImageInLayerX(Array2D_8_8& image, int imageCode, Direction viewDirection, Angle rotate) {
    auto table = ImageLib::get(imageCode);

    if (viewDirection == X_DESCEND) {
        switch (rotate) {
        case ANGLE_0:
            for (int z = 7; z > -1; --z) {
                for (int y = 0; y < 8; ++y) {
                    image[z][y] = table[7-z][y];
                }
            }
            break;
        case ANGLE_90:
            for (int y = 7; y > -1; --y) {
                for (int z = 7; z > -1; --z) {
                    image[z][y] = table[7-y][7-z];
                }
            }
            break;
        case ANGLE_180:
            for (int z = 0; z < 8; ++z) {
                for (int y = 7; y > -1; --y) {
                    image[z][y] = table[z][7-y];
                }
            }
            break;
        case ANGLE_270:
            for (int y = 0; y < 8; ++y) {
                for (int z = 0; z < 8; ++z) {
                    image[z][y] = table[y][z];
                }
            }
            break;
        default:
            break;
        }
    }
    else if (viewDirection == X_ASCEND) {
        switch (rotate) {
        case ANGLE_0:
            for (int z = 7; z > -1; --z) {
                for (int y = 7; y > -1; --y) {
                    image[z][y] = table[7-z][7-y];
                }
            }
            break;
        case ANGLE_90:
            for (int y = 0; y < 8; ++y) {
                for (int z = 7; z > -1; --z) {
                    image[z][y] = table[y][7-z];
                }
            }
            break;
        case ANGLE_180:
            for (int z = 0; z < 8; ++z) {
                for (int y = 0; y < 8; ++y) {
                    image[z][y] = table[z][y];
                }
            }
            break;
        case ANGLE_270:
            for (int y = 7; y > -1; --y) {
                for (int z = 0; z < 8; ++z) {
                    image[z][y] = table[7-y][z];
                }
            }
            break;
        }
    }
    else {
        for (int y = 7; y > -1; --y) {
            for (int z = 0; z < 8; ++z) {
                image[z][y] = LED_OFF;
            }
        }
    }
}


/*****************************************
 *
 *   Copy (or move) layer
 *     copy: set clearZFrom to false
 *     move: set clearZFrom to true
 *
******************************************/
void LedCube::copyLayerX(int xFrom, int xTo, bool clearXFrom) {
    if (clearXFrom) {
        for (int y = 0; y < 8; ++y) {
            for (int z = 0; z < 8; ++z) {
                ledsBuff[z][xTo][y] = ledsBuff[z][xFrom][y];
                ledsBuff[z][xFrom][y] = LED_OFF;
            }
        }
    }
    else {
        for (int y = 0; y < 8; ++y) {
            for (int z = 0; z < 8; ++z) {
                ledsBuff[z][xTo][y] = ledsBuff[z][xFrom][y];
            }
        }
    }
}

void LedCube::copyLayerY(int yFrom, int yTo, bool clearYFrom) {
    if (clearYFrom) {
        for (int x = 0; x < 8; ++x) {
            for (int z = 0; z < 8; ++z) {
                ledsBuff[z][x][yTo] = ledsBuff[z][x][yFrom];
                ledsBuff[z][x][yFrom] = LED_OFF;
            }
        }
    }
    else {
        for (int x = 0; x < 8; ++x) {
            for (int z = 0; z < 8; ++z) {
                ledsBuff[z][x][yTo] = ledsBuff[z][x][yFrom];
            }
        }
    }
}

void LedCube::copyLayerZ(int zFrom, int zTo, bool clearZFrom) {
    if (clearZFrom) {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                ledsBuff[zTo][x][y] = ledsBuff[zFrom][x][y];
                ledsBuff[zFrom][x][y] = LED_OFF;
            }
        }
    }
    else {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                ledsBuff[zTo][x][y] = ledsBuff[zFrom][x][y];
            }
        }
    }
}


/*********************************
 *   Light a cube (cuboid)
 *   line(A, B) is diagonal line
 *********************************/
void LedCube::lightCube(const Vertex& A, const Vertex& B, FillType fill) {
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
        lightRowXY(minX, minY, minZ, maxZ, LED_ON);
        lightRowXY(minX, maxY, minZ, maxZ, LED_ON);
        lightRowXY(maxX, minY, minZ, maxZ, LED_ON);
        lightRowXY(maxX, maxY, minZ, maxZ, LED_ON);
        // parallel to y
        lightRowXZ(minX, minZ, minY + 1, maxY - 1, LED_ON);
        lightRowXZ(minX, maxZ, minY + 1, maxY - 1, LED_ON);
        lightRowXZ(maxX, minZ, minY + 1, maxY - 1, LED_ON);
        lightRowXZ(maxX, maxZ, minY + 1, maxY - 1, LED_ON);
        // parallel to x
        lightRowYZ(minY, minZ, minX + 1, maxX - 1, LED_ON);
        lightRowYZ(minY, maxZ, minX + 1, maxX - 1, LED_ON);
        lightRowYZ(maxY, minZ, minX + 1, maxX - 1, LED_ON);
        lightRowYZ(maxY, maxZ, minX + 1, maxX - 1, LED_ON);
    }
    else if (fill == FILL_SURFACE) {
        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= minY; ++y) {
                ledsBuff[minZ][x][y] = LED_ON;
                ledsBuff[maxZ][x][y] = LED_ON;
            }
        }
        for (int x = minX; x <= maxX; ++x) {
            for (int z = minZ; z <= maxZ; ++z) {
                ledsBuff[z][x][minY] = LED_ON;
                ledsBuff[z][x][maxY] = LED_ON;
            }
        }
        for (int y = minY; y <= maxY; ++y) {
            for (int z = minZ; z <= maxZ; ++z) {
                ledsBuff[z][minX][y] = LED_ON;
                ledsBuff[z][maxX][y] = LED_ON;
            }
        }
    }
    else if (fill == FILL_SOLID) {
        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= maxY; ++y) {
                for (int z = minZ; z <= maxZ; ++z) {
                    ledsBuff[z][x][y] = LED_ON;
                }
            }
        }
    }
}


/*********************************
 *   Light a square (rectangle)
 *   line(A, B) is diagonal line
*********************************/
void LedCube::lightSqure(const Vertex& A, const Vertex& B, FillType fill) {
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


void LedCube::lightSqureInLayerZ(int z, int minX, int maxX, int minY, int maxY, FillType fill) {
    if (fill == FILL_EDGE) {
        for (int x = minX; x <= maxX; ++x) {
            ledsBuff[z][x][minY] = LED_ON;
            ledsBuff[z][x][maxY] = LED_ON;
        }
        for (int y = minY + 1; y < maxY; ++y) {
            ledsBuff[z][minX][y] = LED_ON;
            ledsBuff[z][maxX][y] = LED_ON;
        }
    }
    else {
        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= maxY; ++y) {
                ledsBuff[z][x][y] = LED_ON;
            }
        }
    }
}

void LedCube::lightSqureInLayerY(int y, int minX, int maxX, int minZ, int maxZ, FillType fill) {
    if (fill == FILL_EDGE) {
        for (int x = minX; x <= maxX; ++x) {
            ledsBuff[minZ][x][y] = LED_ON;
            ledsBuff[maxZ][x][y] = LED_ON;
        }
        for (int z = minZ + 1; z < maxZ; ++z) {
            ledsBuff[z][minX][y] = LED_ON;
            ledsBuff[z][maxX][y] = LED_ON;
        }
    }
    else {
        for (int x = minX; x <= maxX; ++x) {
            for (int z = minZ; z <= maxZ; ++z) {
                ledsBuff[z][x][y] = LED_ON;
            }
        }
    }
}

void LedCube::lightSqureInLayerX(int x, int minY, int maxY, int minZ, int maxZ, FillType fill) {
    if (fill == FILL_EDGE) {
        for (int y = minY; y <= maxY; ++y) {
            ledsBuff[minZ][x][y] = LED_ON;
            ledsBuff[maxZ][x][y] = LED_ON;
        }
        for (int z = minZ + 1; z < maxZ; ++z) {
            ledsBuff[z][x][minY] = LED_ON;
            ledsBuff[z][x][maxY] = LED_ON;
        }
    }
    else {
        for (int y = minY; y <= maxY; ++y) {
            for (int z = minZ; z <= maxZ; ++z) {
                ledsBuff[z][x][y] = LED_ON;
            }
        }
    }
}


/*******************************************
 *
 *   Light a circle 
 *     Valid diameter: 1, 2, 3, 4
 *
*******************************************/
void LedCube::lightCircleInLayerX(int x, int diameter, FillType fill) {
    if (fill == FILL_EDGE) {
        lightLayerX(x, Image_Circle_Edge_1 + diameter - 1, X_ASCEND, ANGLE_0);
    }
    else if (fill == FILL_SOLID || fill == FILL_SURFACE) {
        lightLayerX(x, Image_Circle_Solid_1 + diameter - 1, X_ASCEND, ANGLE_0);
    }
}

void LedCube::lightCircleInLayerY(int y, int diameter, FillType fill) {
    if (fill == FILL_EDGE) {
        lightLayerY(y, Image_Circle_Edge_1 + diameter - 1, Y_ASCEND, ANGLE_0);
    }
    else if (fill == FILL_SOLID || fill == FILL_SURFACE) {
        lightLayerY(y, Image_Circle_Solid_1 + diameter - 1, Y_ASCEND, ANGLE_0);
    }
}

void LedCube::lightCircleInLayerZ(int z, int diameter, FillType fill) {
    if (fill == FILL_EDGE) {
        lightLayerZ(z, Image_Circle_Edge_1 + diameter - 1, Z_ASCEND, ANGLE_0);
    }
    else if (fill == FILL_SOLID || fill == FILL_SURFACE) {
        lightLayerZ(z, Image_Circle_Solid_1 + diameter - 1, Z_ASCEND, ANGLE_0);
    }
}

