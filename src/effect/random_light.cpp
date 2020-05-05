#include "random_light.h"
#include "../driver/cube.h"
#include <algorithm>
#include <vector>

extern LedCube cube;


void RandomLightEffect::show() {
    // clear
    cube.lock();
    cube.clear();
    cube.unlock();

    std::vector<int> randomLeds;
    randomLeds.reserve(512);
    for (int i = 0; i < 512; ++i)
        randomLeds.push_back(i);


    std::random_shuffle(randomLeds.begin(), randomLeds.end());

    // light on
    for (int i = 0; i < count_; ++i) {
        cube.lock();
        int idx = randomLeds[i];
        cube(idx % 8, idx % 64 / 8, idx / 64) = LED_ON;
        cube.unlock();
        sleepMs(interval_);
    }

    // light off
    for (int i = 0; i < count_; ++i) {
        cube.lock();
        int idx = randomLeds[i];
        cube(idx % 8, idx % 64 / 8, idx / 64) = LED_OFF;
        cube.unlock();
        sleepMs(interval_);
    }
}
