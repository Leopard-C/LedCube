#include "random_drop_point.h"
#include "../utility/utils.h"

void RandomDropPointEffect::show() {
    for (auto direction : directions_)
        show(direction);
}

void RandomDropPointEffect::show(Direction direction) {
    switch(direction) {
    case X_ASCEND: {
        Call(cube.clear());
        Call(cube.lightLayerX(0, LED_ON));
        pause();
        std::vector<int> vec = util::getRandomArray(64);
        for (int i = 0; i < 64; ++i) {
            int y = vec[i] / 8;
            int z = vec[i] % 8;
            for (int x = 1; x < 8; ++x) {
                cube.lock();
                cube(x - 1, y, z) = LED_OFF;
                cube(x, y, z) = LED_ON;
                cube.unlock();
                pause();
            }
        }
        break;
    }
    case X_DESCEND: {
        Call(cube.clear());
        Call(cube.lightLayerX(7, LED_ON));
        pause();
        std::vector<int> vec = util::getRandomArray(64);
        for (int i = 0; i < 64; ++i) {
            int y = vec[i] / 8;
            int z = vec[i] % 8;
            for (int x = 6; x > -1; --x) {
                cube.lock();
                cube(x + 1, y, z) = LED_OFF;
                cube(x, y, z) = LED_ON;
                cube.unlock();
                pause();
            }
        }
        break;
    }
    case Y_ASCEND: {
        Call(cube.clear());
        Call(cube.lightLayerY(0, LED_ON));
        pause();
        std::vector<int> vec = util::getRandomArray(64);
        for (int i = 0; i < 64; ++i) {
            int x = vec[i] / 8;
            int z = vec[i] % 8;
            for (int y = 1; y < 8; ++y) {
                cube.lock();
                cube(x, y - 1, z) = LED_OFF;
                cube(x, y, z) = LED_ON;
                cube.unlock();
                pause();
            }
        }
        break;
    }
    case Y_DESCEND: {
        Call(cube.clear());
        Call(cube.lightLayerY(7, LED_ON));
        pause();
        std::vector<int> vec = util::getRandomArray(64);
        for (int i = 0; i < 64; ++i) {
            int x = vec[i] / 8;
            int z = vec[i] % 8;
            for (int y = 6; y > -1; --y) {
                cube.lock();
                cube(x, y + 1, z) = LED_OFF;
                cube(x, y, z) = LED_ON;
                cube.unlock();
                pause();
            }
        }
        break;
    }
    case Z_ASCEND: {
        Call(cube.clear());
        Call(cube.lightLayerZ(0, LED_ON));
        pause();
        std::vector<int> vec = util::getRandomArray(64);
        for (int i = 0; i < 64; ++i) {
            int x = vec[i] / 8;
            int y = vec[i] % 8;
            for (int z = 1; z < 8; ++z) {
                cube.lock();
                cube(x, y, z - 1) = LED_OFF;
                cube(x, y, z) = LED_ON;
                cube.unlock();
                pause();
            }
        }
        break;
    }
    case Z_DESCEND: {
        Call(cube.clear());
        Call(cube.lightLayerZ(7, LED_ON));
        pause();
        std::vector<int> vec = util::getRandomArray(64);
        for (int i = 0; i < 64; ++i) {
            int x = vec[i] / 8;
            int y = vec[i] % 8;
            for (int z = 6; z > -1; --z) {
                cube.lock();
                cube(x, y, z + 1) = LED_OFF;
                cube(x, y, z) = LED_ON;
                cube.unlock();
                pause();
            }
        }
        break;
    }
    default:
        break;
    }
}
