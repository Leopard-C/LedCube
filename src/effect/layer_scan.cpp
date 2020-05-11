#include "./layer_scan.h"
#include "../driver/cube.h"
#include "../utility/image_lib.h"
#include "../utility/utils.h"
#include <algorithm>

extern LedCube cube;


void LayerScanEffect::show() {
    for (auto& event : events_) {
        for (auto imageCode : imagesCode_) {
            show(imageCode, event.viewDirection, event.scanDirection,
                 event.rotate, event.together, event.interval1, event.interval2);
        }
    }
}

void LayerScanEffect::show(int imageCode, Direction viewDirection, Direction scanDirection,
        Angle rotate, int together, int interval1, int interval2)
{
    Call(cube.clear());

    if (imageCode == ' ') {
        sleepMs(interval2);
        return;
    }

    LedCube::Array2D_8_8 image;

    if (viewDirection == X_ASCEND || viewDirection == X_DESCEND) {
        cube.getImageInLayerX(image, imageCode, viewDirection, rotate);
        if (scanDirection == X_ASCEND) {
            for (int x = 0; x < 7 + together; ++x) {
                if (x - together > -1)
                    cube.lightLayerX(x - together, LED_OFF);
                if (x < 8)
                    cube.lightLayerX(x, image);
                cube.update();
                sleepMs(interval1);
            }
        }
        else if (scanDirection == X_DESCEND) {
            for (int x = 7; x > -together; --x) {
                if (x + together < 8)
                    cube.lightLayerX(x + together, LED_OFF);
                if (x > -1)
                    cube.lightLayerX(x, image);
                cube.update();
                sleepMs(interval1);
            }
        }
    }
    else if (viewDirection == Y_ASCEND || viewDirection == Y_DESCEND) {
        cube.getImageInLayerY(image, imageCode, viewDirection, rotate);
        if (scanDirection == Y_ASCEND) {
            for (int y = 0; y < 7 + together; ++y) {
                if (y - together > -1)
                    cube.lightLayerY(y - together, LED_OFF);
                if (y < 8)
                    cube.lightLayerY(y, image);
                cube.update();
                sleepMs(interval1);
            }
        } 
        else if (scanDirection == Y_DESCEND) {
            for (int y = 7; y > -together; --y) {
                if (y + together < 8)
                    cube.lightLayerY(y + together, LED_OFF);
                if (y > -1)
                    cube.lightLayerY(y, image);
                cube.update();
                sleepMs(interval1);
            }
        }
    }
    else if (viewDirection == Z_ASCEND || viewDirection == Z_DESCEND) {
        cube.getImageInLayerZ(image, imageCode, viewDirection, rotate);
        if (scanDirection == Z_ASCEND) {
            for (int z = 0; z < 7 + together; ++z) {
                if (z - together > -1)
                    cube.lightLayerZ(z - together, LED_OFF);
                if (z < 8)
                    cube.lightLayerZ(z, image);
                cube.update();
                sleepMs(interval1);
            }
        }
        else if (scanDirection == Z_DESCEND) {
            for (int z = 7; z > -together; --z) {
                if (z + together < 8)
                    cube.lightLayerZ(z + together, LED_OFF);
                if (z < 8)
                    cube.lightLayerZ(z, image);
                cube.update();
                sleepMs(interval1);
            }
        }
    }

    sleepMs(interval2);
}


bool LayerScanEffect::readFromFP(FILE* fp) {
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
                    char rotate[12] = { 0 };
                    int together, interval1, interval2;
                    fscanf(fp, "%s %s %s %d %d %d", viewDirection, scanDirection,
                            rotate, &together, &interval1, &interval2);
                    events_.emplace_back(
                            util::getDirection(viewDirection), util::getDirection(scanDirection),
                            util::getAngle(rotate), together, interval1, interval2);
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


