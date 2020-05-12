#include "fireworks_from_center.h"
#include "../driver/cube_extend.h"
#include "../utility/utils.h"
#include "../utility/image_lib.h"


void FireworksFromCenterEffect::show() {
    for (auto& event : events_) {
        show(event.shapeType, event.fillType, event.interval1, event.interval2, event.interval3);
    }
}

void FireworksFromCenterEffect::show(ShapeType shapeType, FillType fillType,
        int interval1, int interval2, int interval3)
{
    cube.clear();
    cube(3, 3, 0) = LED_ON;
    cube.update();
    sleepMs(interval1);
    for (int z = 1; z < 7; ++z) {
        cube(3, 3, z) = LED_ON;
        cube(3, 3, z - 1) = LED_OFF;
        cube.update();
        sleepMs(interval1);
    }
    if (shapeType == RECTANGLE) {
        for (int i = 0; i < 4; ++i) {
            if (fillType == FILL_EDGE)
                cube.lightLayerZ(7, LED_OFF);
            cube.lightSqure({3-i, 3-i, 7}, {4+i, 4+i, 7}, fillType);
            cube.update();
            sleepMs(interval2);
        }
    }
    else if (shapeType == CIRCLE) {
        for (int i = 0; i < 4; ++i) {
            if (fillType == FILL_EDGE) {
                cube.lightLayerZ(7, LED_OFF);
                cube.lightLayerZ(7, Image_Circle_Edge_1 + i, Z_ASCEND, ANGLE_0);
            }
            else {
                cube.lightLayerZ(7, Image_Circle_Solid_1 + i, Z_ASCEND, ANGLE_0);
            }
            cube.update();
            sleepMs(interval2);
        }
    }
}

bool FireworksFromCenterEffect::readFromFP(FILE* fp) {
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
                    char shapeType[16] = { 0 };
                    char fillType[16] = { 0 };
                    int interval1, interval2, interval3;
                    fscanf(fp, "%s %s %d %d %d",
                            shapeType, fillType, &interval1, &interval2, &interval3);
                    events_.emplace_back(util::getShape(shapeType),  util::getFillType(fillType),
                            interval1, interval2, interval3);
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

