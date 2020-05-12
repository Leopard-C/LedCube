#include "./mode_3.h"
#include "../../driver/cube_extend.h"
#include "../../utility/utils.h"
#include <chrono>


void RiseAndFallMode3Effect::show() {
    for (auto& event : events_) {
        show(event.layer, event.param, event.count, event.interval1, event.interval2);
    }
}

void RiseAndFallMode3Effect::show(Layer layer, int param, int count, int interval1, int interval2) {
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

    //for (int i = 0; i < 8; ++i) {
    //    cube(i, i, currZ[i]) = LED_ON;
    //}
    //cube.update();
    //sleepMs(100);

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
                case LAYER_XY45:
                    cube(i, i, currZ[i]) = LED_OFF;
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    if (i == 0)
                        flag = true;
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube(i, i, currZ[i]) = LED_ON;
                    break;
                case LAYER_XY135:
                    cube(i, 7-i, currZ[i]) = LED_OFF;
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    if (i == 0)
                        flag = true;
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube(i, 7-i, currZ[i]) = LED_ON;
                    break;
                case LAYER_X:
                    cube(param, i, currZ[i]) = LED_OFF;
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    if (i == 0)
                        flag = true;
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube(param, i, currZ[i]) = LED_ON;
                    break;
                case LAYER_Y:
                    cube(i, param, currZ[i]) = LED_OFF;
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    if (i == 0)
                        flag = true;
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube(i, param, currZ[i]) = LED_ON;
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


bool RiseAndFallMode3Effect::readFromFP(FILE* fp) {
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
                    int param;
                    int count, interval1, interval2;
                    fscanf(fp, "%s %d %d %d %d", layer, &param, &count, &interval1, &interval2);
                    events_.emplace_back(util::getLayer(layer), param, count, interval1, interval2);
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


