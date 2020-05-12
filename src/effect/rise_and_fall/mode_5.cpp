#include "./mode_5.h"
#include "../../driver/cube_extend.h"
#include "../../utility/utils.h"
#include <chrono>


void RiseAndFallMode5Effect::show() {
    for (auto& event : events_) {
        if (event.layer == LAYER_XY45 || event.layer == LAYER_XY135)
            showLayerXY(event.layer, event.count, event.interval1, event.interval2);
        else
            showLayerXorYorZ(event.layer, event.count, event.interval1, event.interval2);
    }
}

void RiseAndFallMode5Effect::showLayerXorYorZ(Layer layer, int count, int interval1, int interval2) {
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
    bool flag = false;

    while (true) {
        int ct = 10000 * interval1;
        while (--ct);
        for (int i = 0; i < 8; ++i) {
            ++currTs[i];
            int nextTsI = nextTsIdx[i];
            if (currTs[i] == constTs[nextTsI]) {
                switch (layer) {
                case LAYER_X:
                    cube.lightRowYZ(i, currZ[i], LED_OFF);
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    if (i == 0)
                        flag = true;
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube.lightRowYZ(i, currZ[i], LED_ON);
                    break;
                case LAYER_Y:
                    cube.lightRowXZ(i, currZ[i], LED_OFF);
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    if (i == 0)
                        flag = true;
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube.lightRowXZ(i, currZ[i], LED_ON);
                    break;
                default:
                    break;
                }
            }
            cube.update();
            if (currTs[i] == 2000)
                currTs[i] = 0;
        }

        if (flag && currZ[0] == 0) {
            flag = false;
            ++countTime;
            if (countTime > count) {
                break;
            }
        }

    }

    sleepMs(interval2);
    Call(cube.clear());
}

void RiseAndFallMode5Effect::showLayerXY(Layer layer, int count, int interval1, int interval2) {
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
    bool flag = false;

    while (true) {
        int ct = 10000 * interval1;
        while (--ct);
        for (int i = 0; i < 15; ++i) {
            ++currTs[i];
            int nextTsI = nextTsIdx[i];
            if (currTs[i] == constTs[nextTsI]) {
                if (layer == LAYER_XY45) {
                    lightXY135(i, currZ[i] >> 1, LED_OFF);
                    if (constTs[nextTsI] > 1000) {
                        --currZ[i];
                    }
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 28;
                    lightXY135(i, currZ[i] >> 1, LED_ON);
                }
                else { //LAYER_XY135:
                    lightXY45(i - 7, currZ[i] >> 1, LED_OFF);
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 28;
                    lightXY45(i - 7, currZ[i] >> 1, LED_ON);
                }
                if (i == 0)
                    flag = true;
            }
            if (currTs[i] == 2000)
                currTs[i] = 0;
        }

        cube.update();

        if (flag && currZ[0] == 0) {
            flag = false;
            ++countTime;
            if (countTime > count) {
                break;
            }
        }
    }

    sleepMs(interval2);
    Call(cube.clear());
}


void RiseAndFallMode5Effect::lightXY45(int c, int z, LedState state) {
    for (int x = 0; x < 8; ++x) {
        int y = x + c;
        if (y > -1 && y < 8)
            cube(x, y, z) = state;
    }
}

void RiseAndFallMode5Effect::lightXY135(int c, int z, LedState state) {
    for (int x = 0; x < 8; ++x) {
        int y = c - x;
        if (y > -1 && y < 8)
            cube(x, y, z) = state;
    }
}

bool RiseAndFallMode5Effect::readFromFP(FILE* fp) {
    while (!feof(fp)) {
        char tag1[32] = { 0 };
        fscanf(fp, "%s", tag1);
        util::toUpperCase(tag1, strlen(tag1));

        if (strcmp(tag1, "<EVENTS>") == 0) {
            while (true) {
                char tag2[32] = { 0 };
                fscanf(fp, "%s", tag2);
                util::toUpperCase(tag2, strlen(tag2));
                if (strcmp(tag2, "<EVENT>") == 0) {
                    char layer[16] = { 0 };
                    int count, interval1, interval2;
                    fscanf(fp, "%s %d %d %d", layer, &count, &interval1, &interval2);
                    events_.emplace_back(util::getLayer(layer), count, interval1, interval2);
                }
                else if (strcmp(tag2, "<END_EVENTS>") == 0) {
                    break;
                }
                else if (strcmp(tag2, "<END>") == 0) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else if (strcmp(tag1, "<END>") == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    return true;
}




