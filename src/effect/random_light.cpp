#include "random_light.h"
#include "../driver/cube.h"
#include "../utility/utils.h"
#include <algorithm>
#include <vector>
#include <cstring>

extern LedCube cube;


void RandomLightEffect::show() {
    std::vector<int> randomLeds;
    randomLeds.reserve(512);
    for (int i = 0; i < 512; ++i)
        randomLeds.push_back(i);

    for (auto& event : events_) {
        if (event.state == LED_ON) {
            // clear
            Call(cube.clear());
            std::random_shuffle(randomLeds.begin(), randomLeds.end());
        }

        int i;
        for (i = 0; i < event.maxNum; i += event.together) {
            for (int k = i; k - i < event.together && k < event.maxNum; ++k) {
                int idx = randomLeds[k];
                cube(idx % 8, idx % 64 / 8, idx / 64) = event.state;
            }
            cube.update();
            sleepMs(event.interval1);
        }

        sleepMs(event.interval2);
    }
}

bool RandomLightEffect::readFromFP(FILE* fp) {
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
                    char ledState[16] = { 0 };
                    int together, maxNum, interval1, interval2;
                    fscanf(fp, "%s %d %d %d %d", ledState, &together, &maxNum, &interval1, &interval2);
                    if (strcmp(ledState, "LED_ON") == 0)
                        events_.emplace_back(LED_ON, together, maxNum, interval1, interval2);
                    else
                        events_.emplace_back(LED_OFF, together, maxNum, interval1, interval2);
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

