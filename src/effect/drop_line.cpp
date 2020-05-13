#include "drop_line.h"
#include "../utility/image_lib.h"


void DropLineEffect::show() {
    for (auto& event : events_) {
        for (auto imageCode : imagesCode_) {
            show(imageCode, event.viewDirection, event.dropDirection, event.parallel, event.rotate,
                    event.together, event.interval1, event.interval2);
        }
    }
}

void DropLineEffect::show(int imageCode, Direction viewDirection, Direction dropDirection,
        Direction parallel, Angle rotate, int together, int interval1, int interval2)
{
    Call(cube.clear());

    if (imageCode == ' ') {
        sleepMs(interval2);
        return;
    }

    LedCube::Array2D_8_8 image;

    if (viewDirection == X_ASCEND || viewDirection == X_DESCEND) {
        cube.getImageInLayerX(image, imageCode, viewDirection, rotate);
        if (dropDirection == X_ASCEND) {
            Call(cube.lightLayerX(0, image));
            sleepMs(interval1);
            if (parallel == PARALLEL_Y) {
                for (int z = 0; z < 8; ++z) {
                    for (int x = 1; x < 7 + together; ++x) {
                        if (x - together > -1)
                            cube.lightRowXZ(x - together, z, LED_OFF);
                        if (x < 8)
                            cube.lightRowXZ(x, z, image[z]);
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }
            else if (parallel == PARALLEL_Z) {
                for (int y = 0; y < 8; ++y) {
                    for (int x = 1; x < 7 + together; ++x) {
                        if (x - together > -1)
                            cube.lightRowXY(x - together, y, LED_OFF);
                        if (x < 8)
                            cube.lightRowXY(x, y, util::getCol(image, y));
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }
        }//dropDirection
        else if (dropDirection == X_DESCEND) {
            Call(cube.lightLayerX(7, image));
            sleepMs(interval1);
            if (parallel == PARALLEL_Y) {
                for (int z = 0; z < 8; ++z) {
                    for (int x = 6; x > -together; --x) {
                        if (x + together < 8)
                            cube.lightRowXZ(x + together, z, LED_OFF);
                        if (x > -1)
                            cube.lightRowXZ(x, z, image[z]);
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }
            else if (parallel == PARALLEL_Z) {
                for (int y = 0; y < 8; ++y) {
                    for (int x = 6; x > -together; --x) {
                        if (x + together < 8)
                            cube.lightRowXY(x + together, y, LED_OFF);
                        if (x > -1)
                            cube.lightRowXY(x, y, util::getCol(image, y));
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }
        } //dropDirection
    }//viewDirection

    else if (viewDirection == Y_ASCEND || viewDirection == Y_DESCEND) {
        cube.getImageInLayerY(image, imageCode, viewDirection, rotate);
        if (dropDirection == Y_ASCEND) {
            Call(cube.lightLayerY(0, image));
            sleepMs(interval1);
            if (parallel == PARALLEL_X) {
                for (int z = 0; z < 8; ++z) {
                    for (int y = 1; y < 7 + together; ++y) {
                        if (y - together > -1)
                            cube.lightRowYZ(y - together, z, LED_OFF);
                        if (y < 8)
                            cube.lightRowYZ(y, z, image[z]);
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }
            else if (parallel == PARALLEL_Z) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 1; y < 7 + together; ++y) {
                        if (y - together > -1)
                            cube.lightRowXY(x, y - together, LED_OFF);
                        if (y < 8)
                            cube.lightRowXY(x, y, util::getCol(image, x));
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            } //parallel
        } //dropDirection
        else if (dropDirection == Y_DESCEND) {
            Call(cube.lightLayerY(7, image));
            sleepMs(interval1);
            if (parallel == PARALLEL_X) {
                for (int z = 0; z < 8; ++z) {
                    for (int y = 6; y > -together; --y) {
                        if (y + together < 8)
                            cube.lightRowYZ(y + together, z, LED_OFF);
                        if (y > -1)
                            cube.lightRowYZ(y, z, image[z]);
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }//parallel
            else if (parallel == PARALLEL_Z) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 6; y > -together; --y) {
                        if (y + together < 8)
                            cube.lightRowXY(x, y + together, LED_OFF);
                        if (y > -1)
                            cube.lightRowXY(x, y, util::getCol(image, x));
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            } //parallel
        }//dropDirection
    } //viewDirection

    else if (viewDirection == Z_ASCEND || viewDirection == Z_DESCEND) {
        cube.getImageInLayerZ(image, imageCode, viewDirection, rotate);
        if (dropDirection == Z_ASCEND) {
            Call(cube.lightLayerZ(0, image));
            sleepMs(interval1);
            if (parallel == PARALLEL_X) {
                for (int y = 0; y < 8; ++y) {
                    for (int z = 1; z < 7 + together; ++z) {
                        if (z - together > -1)
                            cube.lightRowYZ(y, z - together, LED_OFF);
                        if (z < 8)
                            cube.lightRowYZ(y, z, util::getCol(image, y));
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }//parallel
            else if (parallel == PARALLEL_Y) {
                for (int x = 0; x < 8; ++x) {
                    for (int z = 1; z < 7 + together; ++z) {
                        if (z - together > -1)
                            cube.lightRowXZ(x, z - together, LED_OFF);
                        if (z < 8)
                            cube.lightRowXZ(x, z, image[x]);
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }//parallel
        }//dropDirection
        else if (dropDirection == Z_DESCEND) {
            Call(cube.lightLayerZ(7, image));
            sleepMs(interval1);
            if (parallel == PARALLEL_X) {
                for (int y = 0; y < 8; ++y) {
                    for (int z = 6; z > -together; --z) {
                        if (z + together < 8)
                            cube.lightRowYZ(y, z + together, LED_OFF);
                        if (z > -1)
                            cube.lightRowYZ(y, z, util::getCol(image, y));
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }//parallel
            else if (parallel == PARALLEL_Y) {
                for (int x = 0; x < 8; ++x) {
                    for (int z = 6; z > -together; --z) {
                        if (z + together < 8)
                            cube.lightRowXZ(x, z + together, LED_OFF);
                        if (z > -1)
                            cube.lightRowXZ(x, z, image[x]);
                        cube.update();
                        sleepMs(interval1);
                    }
                }
            }//parallel
        }//dropDirection

    }//viewDirection

    sleepMs(interval2);
}


bool DropLineEffect::readFromFP(FILE* fp) {
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
                    char viewDirection[12] = { 0 };
                    char scanDirection[12] = { 0 };
                    char parallel[12] = { 0 };
                    char rotate[12] = { 0 };
                    int together, interval1, interval2;
                    fscanf(fp, "%s %s %s %s %d %d %d", viewDirection, scanDirection, parallel,
                            rotate, &together, &interval1, &interval2);
                    events_.emplace_back(
                            util::getDirection(viewDirection), util::getDirection(scanDirection),
                            util::getDirection(parallel), util::getAngle(rotate),
                            together, interval1, interval2);
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

