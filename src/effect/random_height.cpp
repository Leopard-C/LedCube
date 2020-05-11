#include "./random_height.h"
#include "../utility/utils.h"
#include <chrono>

void RandomHeightEffect::show() {
    for (auto& event : events_) {
        show(event.together, event.shape, event.duration, event.interval1, event.interval2);
    }
}

void RandomHeightEffect::show(int together, ShapeType shape, int duration, int interval1, int interval2) {
    cube.clear();

    int targetHeight[8][8];
    int currentHeight[8][8];

    std::vector<int> randomArray = util::getRandomArray(together, 64);
    for (int i = 0; i < together; ++i) {
        int x = randomArray[i] / 8;
        int y = randomArray[i] % 8;
        targetHeight[x][y] = rand() % 7 + 1;
        currentHeight[x][y] = 0;
        cube(x, y, 0) = LED_ON;
    }
    cube.update();
    sleepMs(interval1);

    auto start = std::chrono::system_clock::now();

    while (1) {
        auto end = std::chrono::system_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (dur.count() > duration)
            break;
        for (int i = 0; i < together; ++i) {
            int x = randomArray[i] / 8;
            int y = randomArray[i] % 8;
            if (currentHeight[x][y] < targetHeight[x][y]) {
                if (shape == POINT)
                    cube(x, y, currentHeight[x][y]) = LED_OFF;
                ++currentHeight[x][y];
            }
            else if (currentHeight[x][y] > targetHeight[x][y]) {
                cube(x, y, currentHeight[x][y]) = LED_OFF;
                --currentHeight[x][y];
            }
            cube(x, y, currentHeight[x][y]) = LED_ON;
            while (currentHeight[x][y] == targetHeight[x][y]) {
                targetHeight[x][y] = rand() % 8;
            }
        }
        cube.update();
        sleepMs(interval1);
    }

    sleepMs(interval2);
}

bool RandomHeightEffect::readFromFP(FILE* fp) {
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
                    char shapeTypeStr[12] = { 0 };
                    int together, duration, interval1, interval2;
                    fscanf(fp, "%d %s %d %d %d", &together, shapeTypeStr, &duration,
                            &interval1, &interval2);
                    events_.emplace_back(together, util::getShape(shapeTypeStr),
                            duration, interval1, interval2);
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
