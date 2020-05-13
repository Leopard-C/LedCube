#include "random_drop_point.h"
#include "../utility/image_lib.h"


void RandomDropPointEffect::show() {
    for (auto& event : events_) {
        for (auto imageCode : imagesCode_) {
            show(imageCode, event.viewDirection, event.dropDirection, event.rotate,
                    event.togetherView, event.togetherScan, event.interval1, event.interval2);
        }
    }
}

void RandomDropPointEffect::show(int imageCode, Direction viewDirection,
        Direction dropDirection, Angle rotate, int togetherView,
        int togetherScan, int interval1, int interval2)
{
    Call(cube.clear());

    if (imageCode == ' ') {
        sleepMs(interval2);
        return;
    }

    LedCube::Array2D_8_8 image;
    std::vector<int> randomVec = util::getRandomArray(64);

    if (viewDirection == X_ASCEND || viewDirection == X_DESCEND) {
        cube.getImageInLayerX(image, imageCode, viewDirection, rotate);
        if (dropDirection == X_ASCEND) {
            Call(cube.lightLayerX(0, image));
            sleepMs(interval1);
            for (int i = 0; i < 64; i += togetherView) {
                for (int x = 1; x < 7 + togetherScan; ++x) {
                    for (int k = 0; k < togetherView; ++k) {
                        int y = randomVec[i+k] / 8;
                        int z = randomVec[i+k] % 8;
                        if (image[z][y] == LED_OFF)
                            continue;
                        if (x - togetherScan > -1)
                            cube(x - togetherScan, y, z) = LED_OFF;
                        if (x < 8)
                            cube(x, y, z) = LED_ON;
                    }
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }//dropDirection
        else if (dropDirection == X_DESCEND) {
            Call(cube.lightLayerX(7, image));
            sleepMs(interval1);
            for (int i = 0; i < 64; i += togetherView) {
                for (int x = 6; x > -togetherScan; --x) {
                    for (int k = 0; k < togetherView; ++k) {
                        int y = randomVec[i+k] / 8;
                        int z = randomVec[i+k] % 8;
                        if (image[z][y] == LED_OFF)
                            continue;
                        if (x + togetherScan < 8)
                            cube(x + togetherScan, y, z) = LED_OFF;
                        if (x > -1)
                            cube(x, y, z) = LED_ON;
                    }
                    cube.update();
                    sleepMs(interval1);
                }
            }
        } //dropDirection
    }//viewDirection

    else if (viewDirection == Y_ASCEND || viewDirection == Y_DESCEND) {
        cube.getImageInLayerY(image, imageCode, viewDirection, rotate);
        if (dropDirection == Y_ASCEND) {
            Call(cube.lightLayerY(0, image));
            sleepMs(interval1);
            for (int i = 0; i < 64; i += togetherView) {
                for (int y = 1; y < 7 + togetherScan; ++y) {
                    for (int k = 0; k < togetherView; ++k) {
                        int x = randomVec[i+k] / 8;
                        int z = randomVec[i+k] % 8;
                        if (image[z][x] == LED_OFF)
                            continue;
                        if (y - togetherScan > -1)
                            cube(x, y - togetherScan, z) = LED_OFF;
                        if (y < 8)
                            cube(x, y, z) = LED_ON;
                    }
                    cube.update();
                    sleepMs(interval1);
                }
            }
        } //dropDirection
        else if (dropDirection == Y_DESCEND) {
            Call(cube.lightLayerY(7, image));
            sleepMs(interval1);
            for (int i = 0; i < 64; i += togetherView) {
                for (int y = 6; y > -togetherScan; --y) {
                    for (int k = 0; k < togetherView; ++k) {
                        int x = randomVec[i+k] / 8;
                        int z = randomVec[i+k] % 8;
                        if (image[z][x] == LED_OFF)
                            continue;
                        if (y + togetherScan < 8)
                            cube(x, y + togetherScan, z) = LED_OFF;
                        if (y > -1)
                            cube(x, y, z) = LED_ON;
                    }
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }//dropDirection
    } //viewDirection

    else if (viewDirection == Z_ASCEND || viewDirection == Z_DESCEND) {
        cube.getImageInLayerZ(image, imageCode, viewDirection, rotate);
        if (dropDirection == Z_ASCEND) {
            Call(cube.lightLayerZ(0, image));
            sleepMs(interval1);
            for (int i = 0; i < 64; i += togetherView) {
                for (int z = 1; z < 7 + togetherScan; ++z) {
                    for (int k = 0; k < togetherView; ++k) {
                        int x = randomVec[i+k] / 8;
                        int y = randomVec[i+k] % 8;
                        if (image[x][y] == LED_OFF)
                            continue;
                        if (z - togetherScan > -1)
                            cube(x, y, z - togetherScan) = LED_OFF;
                        if (z < 8)
                            cube(x, y, z) = LED_ON;
                    }
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }//dropDirection
        else if (dropDirection == Z_DESCEND) {
            Call(cube.lightLayerZ(7, image));
            sleepMs(interval1);
            for (int i = 0; i < 64; i += togetherView) {
                for (int z = 6; z > -togetherScan; --z) {
                    for (int k = 0; k < togetherView; ++k) {
                        int x = randomVec[i+k] / 8;
                        int y = randomVec[i+k] % 8;
                        if (image[x][y] == LED_OFF)
                            continue;
                        if (z + togetherScan < 8)
                            cube(x, y, z + togetherScan) = LED_OFF;
                        if (z > -1)
                            cube(x, y, z) = LED_ON;
                    }
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }//dropDirection
    }//viewDirection

    sleepMs(interval2);
}


bool RandomDropPointEffect::readFromFP(FILE* fp) {
    while (!feof(fp)) {
        char tag1[32] = { 0 };
        fscanf(fp, "%s", tag1);
        util::toUpperCase(tag1, strlen(tag1));

        if (strcmp(tag1, "<IMAGESCODE>") == 0) {
            while (true) {
                char tag2[32] = { 0 };
                fscanf(fp, "%s", tag2);
                util::toUpperCase(tag2, strlen(tag2));
                if (strcmp(tag2, "<CODE>") == 0) {
                    char imageCodeStr[32] = { 0 };
                    fscanf(fp, "%s", imageCodeStr);
                    int imageCode = ImageLib::getKey(imageCodeStr);
                    if (imageCode != -1)
                        imagesCode_.push_back(imageCode);
                }
                else if (strcmp(tag2, "<END_IMAGESCODE>") == 0) {
                    break;
                }
                else if (strcmp(tag2, "<END>") ==  0) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else if (strcmp(tag1, "<EVENTS>") == 0) {
            while (true) {
                char tag2[32] = { 0 };
                fscanf(fp, "%s", tag2);
                util::toUpperCase(tag2, strlen(tag2));
                if (strcmp(tag2, "<EVENT>") == 0) {
                    char viewDirection[16] = { 0 };
                    char scanDirection[16] = { 0 };
                    char rotate[16] = { 0 };
                    int togetherView, togetherScan, interval1, interval2;
                    fscanf(fp, "%s %s %s %d %d %d %d", viewDirection, scanDirection,
                            rotate, &togetherView, &togetherScan, &interval1, &interval2);
                    events_.emplace_back(
                            util::getDirection(viewDirection), util::getDirection(scanDirection),
                            util::getAngle(rotate), togetherView, togetherScan, interval1, interval2);
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

