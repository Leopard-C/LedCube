#include "layer_scan.h"
#include "../driver/cube.h"

extern LedCube cube;


void LayerScanEffect::show() {
    for (auto direction : directions_) {
        switch (direction) {
        case X_ASCEND:
            for (int x = 0; x < 8; ++x) {
                cube.lock();
                cube.lightLayerX(x, LED_ON);
                cube.unlock();
                sleepMs(interval1_);
                cube.lock();
                cube.lightLayerX(x, LED_OFF);
                cube.unlock();
                sleepMs(interval2_);
            }
            break;
        case X_DESCEND:
            for (int x = 7; x > -1; --x) {
                cube.lock();
                cube.lightLayerX(x, LED_ON);
                cube.unlock();
                sleepMs(interval1_);
                cube.lock();
                cube.lightLayerX(x, LED_OFF);
                cube.unlock();
                sleepMs(interval2_);
            }
            break;
        case Y_ASCEND:
            for (int y = 0; y < 8; ++y) {
                cube.lock();
                cube.lightLayerY(y, LED_ON);
                cube.unlock();
                sleepMs(interval1_);
                cube.lock();
                cube.lightLayerY(y, LED_OFF);
                cube.unlock();
                sleepMs(interval2_);
            }
            break;
        case Y_DESCEND:
            for (int y = 7; y > -1; --y) {
                cube.lock();
                cube.lightLayerY(y, LED_ON);
                cube.unlock();
                sleepMs(interval1_);
                cube.lock();
                cube.lightLayerY(y, LED_OFF);
                cube.unlock();
                sleepMs(interval2_);
            }
            break;
        case Z_ASCEND:
            for (int z = 0; z < 8; ++z) {
                cube.lock();
                cube.lightLayerZ(z, LED_ON);
                cube.unlock();
                sleepMs(interval1_);
                cube.lock();
                cube.lightLayerZ(z, LED_OFF);
                cube.unlock();
                sleepMs(interval2_);
            }
            break;
        case Z_DESCEND:
            for (int z = 7; z > -1; --z) {
                cube.lock();
                cube.lightLayerZ(z, LED_ON);
                cube.unlock();
                sleepMs(interval1_);
                cube.lock();
                cube.lightLayerZ(z, LED_OFF);
                cube.unlock();
                sleepMs(interval2_);
            }
            break;
        default:
            break;
        }
    }
}

