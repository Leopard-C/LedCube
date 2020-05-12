#include "./mode_6.h"
#include "../../driver/cube_extend.h"
#include "../../utility/utils.h"
#include <chrono>


void RiseAndFallMode6Effect::showLayerXorYorZ(Layer layer, int count, int interval1, int interval2) {
    Call(cube.clear());

    if (layer == LAYER_ERROR || layer == LAYER_Z) {
        sleepMs(interval2);
        return;
    }

    const int constTs[14] = {
        246,  359,  454,  546,  640,  753, 1000,
        1246, 1359, 1454, 1546, 1641, 1753, 2000
    };
    int nextTsIdx[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    int currTs[8] = { 0,   246, 359, 454, 546, 640, 753, 1000 };
    int currZ[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    int countTime = 0;
    bool bUpdate = false;
    bool bOffset = false;

    int currOffset = 0;
    Direction direction = Z_ASCEND;

    while (true) {
        int ct = 10000 * interval1;
        while (--ct);
        for (int i = 0; i < 8; ++i) {
            ++currTs[i];
            int nextTsI = nextTsIdx[i];
            if (currTs[i] == constTs[nextTsI]) {
                bUpdate = true;
                bOffset = (i == 0 || i == 7);
                switch (layer) {
                case LAYER_X:
                    cube.lightRowYZ(i, (currZ[i] >> 1) + currOffset, LED_OFF);
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube.lightRowYZ(i, (currZ[i] >> 1) + currOffset, LED_ON);
                    break;
                case LAYER_Y:
                    cube.lightRowXZ(i, (currZ[i] >> 1) + currOffset, LED_OFF);
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube.lightRowXZ(i, (currZ[i] >> 1) + currOffset, LED_ON);
                    break;
                default:
                    break;
                }
            }
            if (currTs[i] == 2000)
                currTs[i] = 0;
        }

        if (bUpdate) {
            bUpdate = false;
            cube.update();

            if (bOffset) {
                bOffset = false;
                if (direction == Z_ASCEND && currZ[0] == 0) {
                    for (int i = currOffset + 4; i > currOffset; --i) {
                        cube.copyLayerZ(i - 1, i, true);
                    }
                    ++currOffset;
                    if (currOffset == 4)
                        direction = Z_DESCEND;
                }
                else if (direction == Z_DESCEND && currZ[0] == 7) {
                    for (int i = currOffset; i < currOffset + 4; ++i) {
                        cube.copyLayerZ(i, i - 1, true);
                    }
                    --currOffset;
                    if (currOffset == 0)
                        direction = Z_ASCEND;
                }

                if (currZ[0] == 0) {
                    ++countTime;
                    if (countTime > count) {
                        break;
                    }
                }
            }
        }
    }

    sleepMs(interval2);
}

void RiseAndFallMode6Effect::showLayerXY(Layer layer, int count, int interval1, int interval2) {
    Call(cube.clear());

    const int constTs[28] = {
        172,  247,  306,  359,  408,  454,  500,  546,
        592,  641,  694,  753,  828,  1000, 1172, 1247,
        1306, 1359, 1408, 1454, 1500, 1546, 1592, 1641,
        1694, 1753, 1828, 2000
    };
    int nextTsIdx[15] = {
        0, 1, 2,  3,  4,  5,  6, 7,
        8, 9, 10, 11, 12, 13, 14
    };

    int currTs[15] = { 
        0,   172,  247,  306,  359,  408,  454,  500,
        546, 592,  641,  694,  753,  828,  1000
    };
    int currZ[15] = {
        0,  1,  2,  3,  4,  5,  6,  7,
        8,  9,  10, 11, 12, 13, 14
    };

    int countTime = 0;

    bool bUpdate = false;
    bool bOffset = false;

    int currOffset = 0;
    Direction direction = Z_ASCEND;

    while (true) {
        int ct = 10000 * interval1;
        while (--ct);
        for (int i = 0; i < 15; ++i) {
            ++currTs[i];
            int nextTsI = nextTsIdx[i];
            if (currTs[i] == constTs[nextTsI]) {
                bUpdate = true;
                bOffset = (i == 0 || i == 14);
                if (layer == LAYER_XY45) {
                    lightXY135(i, (currZ[i] >> 2) + currOffset, LED_OFF);
                    if (constTs[nextTsI] > 1000) {
                        --currZ[i];
                    }
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 28;
                    lightXY135(i, (currZ[i] >> 2) + currOffset, LED_ON);
                }
                else { //LAYER_XY135:
                    lightXY45(i - 7, (currZ[i] >> 2) + currOffset, LED_OFF);
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 28;
                    lightXY45(i - 7, (currZ[i] >> 2) + currOffset, LED_ON);
                }
            }
            cube.update();
            if (currTs[i] == 2000)
                currTs[i] = 0;
        }

        if (bUpdate) {
            bUpdate = false;
            cube.update();

            if (bOffset) {
                bOffset = false;
                if (direction == Z_ASCEND && currZ[0] == 0) {
                    for (int i = currOffset + 4; i > currOffset; --i) {
                        cube.copyLayerZ(i - 1, i, true);
                    }
                    ++currOffset;
                    if (currOffset == 4)
                        direction = Z_DESCEND;
                }
                else if (direction == Z_DESCEND && currZ[0] == 14) {
                    for (int i = currOffset; i < currOffset + 4; ++i) {
                        cube.copyLayerZ(i, i - 1, true);
                    }
                    --currOffset;
                    if (currOffset == 0)
                        direction = Z_ASCEND;
                }

                if (currZ[0] == 0) {
                    ++countTime;
                    if (countTime > count) {
                        break;
                    }
                }
            }
        }
    }

    sleepMs(interval2);
}

