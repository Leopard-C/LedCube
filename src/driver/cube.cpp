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


// private method !!
//
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

    for (int z = 0; z < 8; ++z) {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                leds[z][x][y] = LED_OFF;
                ledsBuff[z][x][y] = LED_OFF;
            }
        }
    }
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
                digitalWrite(vcc[z], HIGH);
                for (int y = 0; y < 8; ++y) {
                    if (leds[z][x][y] == LED_ON) {
                        x74hc154[idx].setOutput(y + 8 * (x % 2));
                        x74hc154[idx].enable(true);
                        // slepp servel nanoseconds
                        // shouldn't use:
                        //   std::this_thread::sleep_for(std::chrono::nanoseconds(100));
                        //   even if you want to sleep 1 ns, it will consume 10000+ ns really
                        for (int i = 0; i < 200; ++i) {
                            //;
                        }
                        x74hc154[idx].enable(false);
                    }
                }
                digitalWrite(vcc[z], LOW);
            }
        }
        mutex_.unlock();
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
    for (int z = 0; z < 8; ++z) {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                ledsBuff[z][x][y] = LED_OFF;
            }
        }
    }
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

void LedCube::showStringInLayerZ(std::string str, int interval, int z, Direction viewDirection, Angle rotate) {
    ImageLib::validate(str);
    for (auto ch : str) {
        lightLayerZ(ch, z, viewDirection, rotate);
        if (ch == ' ')
            std::this_thread::sleep_for(std::chrono::milliseconds(interval / 2));
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

void LedCube::showStringInLayerY(std::string str, int interval, int y, Direction viewDirection, Angle rotate) {
    ImageLib::validate(str);
    for (auto ch : str) {
        lightLayerY(ch, y, viewDirection, rotate);
        if (ch == ' ')
            std::this_thread::sleep_for(std::chrono::milliseconds(interval / 2));
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

void LedCube::showStringInLayerX(std::string str, int interval, int x, Direction viewDirection, Angle rotate) {
    ImageLib::validate(str);
    for (auto ch : str) {
        lightLayerX(ch, x, viewDirection, rotate);
        if (ch == ' ')
            std::this_thread::sleep_for(std::chrono::milliseconds(interval / 2));
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}


/*********************************
 *
 *   Copy (or move) layer
 *
**********************************/
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


