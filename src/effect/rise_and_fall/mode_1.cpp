#include "./mode_1.h"
#include "../../driver/cube_extend.h"
#include "../../utility/utils.h"


void RiseAndFallMode1Effect::show() {
    for (auto& event : events_) {
        Call(cube.clear());
        for (int i = 0; i < event.count; ++i) {
            fall(event.interval1);
            rise(event.interval1);
        }
        sleepMs(event.interval2);
        Call(cube.clear());
    }
}

void RiseAndFallMode1Effect::rise(int interval) {
    int zs[4] = { 0, 0, 0, 0 };

    while (true) {
        cube.clear();
        if (zs[0] == 0) {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
        }
        else if (zs[0] == 1) {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            ++zs[1];
        }
        else if (zs[0] == 2) {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            ++zs[1];
            ++zs[2];
        }

        else if (zs[0] == 8) {
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[1];
            ++zs[2];
            ++zs[3];
        }
        else if (zs[0] == 9) {
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[2];
            ++zs[3];
        }
        else if (zs[0] == 10) {
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[3];
        }
        else if (zs[0] == 11) {
            break;
        }

        else {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            ++zs[1];
            ++zs[2];
            ++zs[3];
        }

        ++zs[0]; 
        cube.update();
        sleepMs(interval);
    }
}

void RiseAndFallMode1Effect::fall(int interval) {
    int zs[4] = { 7, 7, 7, 7 };

    while (true) {
        cube.clear();
        if (zs[0] == 7) {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
        }
        else if (zs[0] == 6) {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            --zs[1];
        }
        else if (zs[0] == 5) {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            --zs[1];
            --zs[2];
        }

        else if (zs[0] == -1) {
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[1];
            --zs[2];
            --zs[3];
        }
        else if (zs[0] == -2) {
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[2];
            --zs[3];
        }
        else if (zs[0] == -3) {
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[3];
        }
        else if (zs[0] == -4) {
            break;
        }

        else {
            cube.lightSqure({ 3, 3, zs[0] }, { 4, 4, zs[0] }, FILL_EDGE);
            cube.lightSqure({ 2, 2, zs[1] }, { 5, 5, zs[1] }, FILL_EDGE);
            cube.lightSqure({ 1, 1, zs[2] }, { 6, 6, zs[2] }, FILL_EDGE);
            cube.lightSqure({ 0, 0, zs[3] }, { 7, 7, zs[3] }, FILL_EDGE);
            --zs[1];
            --zs[2];
            --zs[3];
        }

        --zs[0]; 
        cube.update();
        sleepMs(interval);
    }
}


bool RiseAndFallMode1Effect::readFromFP(FILE* fp) {
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
                    int count, interval1, interval2;
                    fscanf(fp, "%d %d %d", &count, &interval1, &interval2);
                    events_.emplace_back(count, interval1, interval2);
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

