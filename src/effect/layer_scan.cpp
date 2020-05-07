#include "./layer_scan.h"
#include "../driver/cube.h"
#include "../utility/image_lib.h"
#include <algorithm>

extern LedCube cube;


void LayerScanEffect::show() {
    int size = directions_.size();
    for (int i = 0; i < size; ++i) {
        show(directions_[i], subDirections_[i], angles_[i]);
    }
}

void LayerScanEffect::show(Direction direction, Direction subDirection, Angle angle) {
    for (auto code : imagesCode_) {
        Call(cube.clear());

        if (code == ' ') {
            sleepMs(interval2_);
            continue;
        }

        LedCube::Array2D_8_8 image;

        switch (direction) {
        case X_ASCEND:
            cube.getImageInLayerX(image, code, direction, angle);
            if (subDirection == X_ASCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int x = together_; x < 8; ++x) {
                    cube.lightLayerX(x - together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == X_DESCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(7 - i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int x = 7 - together_; x > -1; --x) {
                    cube.lightLayerX(x + together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            break;
        case X_DESCEND:
            cube.getImageInLayerX(image, code, direction, angle);
            if (subDirection == X_DESCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(7 - i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int x = 7 - together_; x > -1; --x) {
                    cube.lightLayerX(x + together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == X_ASCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int x = together_; x < 8; ++x) {
                    cube.lightLayerX(x - together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            break;
        case Y_ASCEND:
            cube.getImageInLayerY(image, code, direction, angle);
            if (subDirection == Y_ASCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int y = together_; y < 8; ++y) {
                    cube.lightLayerY(y - together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Y_DESCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(7 - i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int y = 7 - together_; y > -1; --y) {
                    cube.lightLayerY(y + together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            break;
        case Y_DESCEND:
            cube.getImageInLayerY(image, code, direction, angle);
            if (subDirection == Y_DESCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(7 - i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int y = 7 - together_; y > -1; --y) {
                    cube.lightLayerY(y + together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Y_ASCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int y = together_; y < 8; ++y) {
                    cube.lightLayerY(y - together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            break;
        case Z_ASCEND:
            cube.getImageInLayerZ(image, code, direction, angle);
            if (subDirection == Z_ASCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int z = together_; z < 8; ++z) {
                    cube.lightLayerZ(z - together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Z_DESCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(7 - i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int z = 7 - together_; z > -1; --z) {
                    cube.lightLayerZ(z + together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            break;
        case Z_DESCEND:
            cube.getImageInLayerZ(image, code, direction, angle);
            if (subDirection == Z_DESCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(7 - i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int z = 7 - together_; z > -1; --z) {
                    cube.lightLayerZ(z + together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Z_ASCEND) {
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(i, image);
                }
                cube.update();
                sleepMs(interval1_);
                for (int z = together_; z < 8; ++z) {
                    cube.lightLayerZ(z - together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            break;
        default:
            break;
        }

        sleepMs(interval2_);

    } // end for code

    Call(cube.clear());
}

