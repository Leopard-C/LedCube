#include "./rise_and_fall.h"
#include "../driver/cube_extend.h"


void RiseAndFallEffect::show() {
    for (int i = 0; i < 10; ++i) {
        fall(30);
        rise(30);
    }
}

void RiseAndFallEffect::rise(int interval) {
    int zs[4] = { 0, 0, 0, 0 };

    while (true) {
        cube.clear();
        if (zs[0] == 0) {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
        }
        else if (zs[0] == 1) {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ++zs[1];
        }
        else if (zs[0] == 2) {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ++zs[1];
            ++zs[2];
        }

        else if (zs[0] == 8) {
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[1];
            ++zs[2];
            ++zs[3];
        }
        else if (zs[0] == 9) {
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[2];
            ++zs[3];
        }
        else if (zs[0] == 10) {
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[3];
        }
        else if (zs[0] == 11) {
            break;
        }

        else {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[1];
            ++zs[2];
            ++zs[3];
        }

        ++zs[0]; 
        cube.update();
        sleepMs(interval);
    }
}

void RiseAndFallEffect::fall(int interval) {
    int zs[4] = { 7, 7, 7, 7 };

    while (true) {
        cube.clear();
        if (zs[0] == 7) {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
        }
        else if (zs[0] == 6) {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            --zs[1];
        }
        else if (zs[0] == 5) {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            --zs[1];
            --zs[2];
        }

        else if (zs[0] == -1) {
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[1];
            --zs[2];
            --zs[3];
        }
        else if (zs[0] == -2) {
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[2];
            --zs[3];
        }
        else if (zs[0] == -3) {
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[3];
        }
        else if (zs[0] == -4) {
            break;
        }

        else {
            ext::lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            ext::lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ext::lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ext::lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[1];
            --zs[2];
            --zs[3];
        }

        --zs[0]; 
        cube.update();
        sleepMs(interval);
    }
}
