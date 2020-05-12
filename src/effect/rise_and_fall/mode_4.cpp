#include "./mode_4.h"
#include "../../driver/cube_extend.h"
#include "../../utility/utils.h"
#include <chrono>


void RiseAndFallMode4Effect::show() {
    for (auto& event : events_) {
        show(event.layer, event.interval1, event.interval2, event.interval3);
    }
}

void RiseAndFallMode4Effect::show(Layer layer, int interval1, int interval2, int interval3) {
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

    int divid = interval2 * 100 / interval1;  // not exectly
    int count = 0;
    int offset = 0;

    while (true) {
        int ct = 10000 * interval1;
        while (--ct);

        if ((++count) % divid == 0) {
            if ((++offset) > 7) {
                break;
            }
            if (layer == LAYER_X)
                cube.copyLayerX(offset - 1, offset, true);
            else
                cube.copyLayerY(7 - offset + 1, 7 - offset, true);
            cube.update();
        }

        for (int i = 0; i < 8; ++i) {
            ++currTs[i];
            int nextTsI = nextTsIdx[i];
            if (currTs[i] == constTs[nextTsI]) {
                flag = true;
                if (layer == LAYER_X) {
                    cube(offset, i, currZ[i]) = LED_OFF;
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube(offset, i, currZ[i]) = LED_ON;
                }
                else if (layer == LAYER_Y) {
                    cube(i, 7 - offset, currZ[i]) = LED_OFF;
                    if (constTs[nextTsI] > 1000)
                        --currZ[i];
                    else
                        ++currZ[i];
                    nextTsIdx[i] = (nextTsI + 1) % 14;
                    cube(i, 7 - offset, currZ[i]) = LED_ON;
                }
            }
            if (currTs[i] == 2000)
                currTs[i] = 0;
        }

        if (flag) {
            cube.update();
            flag = false;
        }
    }

    sleepMs(interval3);
    Call(cube.clear());
}


bool RiseAndFallMode4Effect::readFromFP(FILE* fp) {
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
                    int interval1, interval2, interval3;
                    fscanf(fp, "%s %d %d %d", layer, &interval1, &interval2, &interval3);
                    events_.emplace_back(util::getLayer(layer), interval1, interval2, interval3);
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


