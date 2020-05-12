#include "./mode_2.h"
#include "../../driver/cube_extend.h"
#include "../../utility/utils.h"


void RiseAndFallMode2Effect::rise(int interval) {
    int zs[4] = { 0, 0, 0, 0 };

    while (true) {
        cube.clear();
        if (zs[0] == 0) {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
        }
        else if (zs[0] == 1) {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ++zs[1];
        }
        else if (zs[0] == 2) {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ++zs[1];
            ++zs[2];
        }

        else if (zs[0] == 8) {
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            ++zs[1];
            ++zs[2];
            ++zs[3];
        }
        else if (zs[0] == 9) {
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            ++zs[2];
            ++zs[3];
        }
        else if (zs[0] == 10) {
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            ++zs[3];
        }
        else if (zs[0] == 11) {
            break;
        }

        else {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            ++zs[1];
            ++zs[2];
            ++zs[3];
        }

        ++zs[0]; 
        cube.update();
        sleepMs(interval);
    }
}

void RiseAndFallMode2Effect::fall(int interval) {
    int zs[4] = { 7, 7, 7, 7 };

    while (true) {
        cube.clear();
        if (zs[0] == 7) {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
        }
        else if (zs[0] == 6) {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            --zs[1];
        }
        else if (zs[0] == 5) {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            --zs[1];
            --zs[2];
        }

        else if (zs[0] == -1) {
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            --zs[1];
            --zs[2];
            --zs[3];
        }
        else if (zs[0] == -2) {
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            --zs[2];
            --zs[3];
        }
        else if (zs[0] == -3) {
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            --zs[3];
        }
        else if (zs[0] == -4) {
            break;
        }

        else {
            ext::lightCircleInLayerZ(zs[0], 1, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[1], 2, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[2], 3, FILL_EDGE);
            ext::lightCircleInLayerZ(zs[3], 4, FILL_EDGE);
            --zs[1];
            --zs[2];
            --zs[3];
        }

        --zs[0]; 
        cube.update();
        sleepMs(interval);
    }
}

