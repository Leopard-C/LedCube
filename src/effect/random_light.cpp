#include "random_light.h"
#include "../driver/cube.h"
#include <algorithm>
#include <vector>

extern LedCube cube;


void RandomLightEffect::show() {
    std::vector<int> randomLeds;
    randomLeds.reserve(512);
    for (int i = 0; i < 512; ++i)
        randomLeds.push_back(i);

    for (auto state : states_) {
        if (state == LED_ON) {
            // clear
            Call(cube.clear());
            std::random_shuffle(randomLeds.begin(), randomLeds.end());
        }

        for (int i = 0; i < count_; ++i) {
            int idx = randomLeds[i];
            cube(idx % 8, idx % 64 / 8, idx / 64) = state;
            cube.update();
            sleepMs(interval_);
        }
    }
}
