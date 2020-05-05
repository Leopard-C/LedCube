#include "./drop_text.h"
#include "../driver/cube.h"
#include "../utility/image_lib.h"
#include <algorithm>

extern LedCube cube;


void DropTextEffect::setString(const std::string& str) {
    string_ = str;
    ImageLib::validate(string_);
}

void DropTextEffect::show() {
    int size = directions_.size();
    for (int i = 0; i < size; ++i) {
        show(directions_[i], subDirections_[i], angles_[i]);
    }
}

void DropTextEffect::show(Direction direction, Direction subDirection, Angle angle) {
    for (auto ch : string_) {
        Call(cube.clear());

        if (ch == ' ') {
            sleepMs(interval2_ * 2);
            continue;
        }

        LedCube::Array2D_8_8 image;
        switch (direction) {
        case X_ASCEND:
            cube.getImageInLayerX(image, ch, direction, angle);
            if (subDirection == X_ASCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int x = together_; x < 8; ++x) {
                    cube.lock();
                    cube.lightLayerX(x - together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == X_DESCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(7 - i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int x = 7 - together_; x > -1; --x) {
                    cube.lock();
                    cube.lightLayerX(x + together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            break;
        case X_DESCEND:
            cube.getImageInLayerX(image, ch, direction, angle);
            if (subDirection == X_DESCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(7 - i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int x = 7 - together_; x > -1; --x) {
                    cube.lock();
                    cube.lightLayerX(x + together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == X_ASCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerX(i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int x = together_; x < 8; ++x) {
                    cube.lock();
                    cube.lightLayerX(x - together_, LED_OFF);
                    cube.setImageInLayerX(x, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            break;
        case Y_ASCEND:
            cube.getImageInLayerY(image, ch, direction, angle);
            if (subDirection == Y_ASCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int y = together_; y < 8; ++y) {
                    cube.lock();
                    cube.lightLayerY(y - together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Y_DESCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(7 - i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int y = 7 - together_; y > -1; --y) {
                    cube.lock();
                    cube.lightLayerY(y + together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            break;
        case Y_DESCEND:
            cube.getImageInLayerY(image, ch, direction, angle);
            if (subDirection == Y_DESCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(7 - i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int y = 7 - together_; y > -1; --y) {
                    cube.lock();
                    cube.lightLayerY(y + together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Y_ASCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerY(i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int y = together_; y < 8; ++y) {
                    cube.lock();
                    cube.lightLayerY(y - together_, LED_OFF);
                    cube.setImageInLayerY(y, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            break;
        case Z_ASCEND:
            cube.getImageInLayerZ(image, ch, direction, angle);
            if (subDirection == Z_ASCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int z = together_; z < 8; ++z) {
                    cube.lock();
                    cube.lightLayerZ(z - together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Z_DESCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(7 - i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int z = 7 - together_; z > -1; --z) {
                    cube.lock();
                    cube.lightLayerZ(z + together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            break;
        case Z_DESCEND:
            cube.getImageInLayerZ(image, ch, direction, angle);
            if (subDirection == Z_DESCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(7 - i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int z = 7 - together_; z > -1; --z) {
                    cube.lock();
                    cube.lightLayerZ(z + together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            else if (subDirection == Z_ASCEND) {
                cube.lock();
                for (int i = 0; i < together_; ++i) {
                    cube.setImageInLayerZ(i, image);
                }
                cube.unlock();
                sleepMs(interval1_);
                for (int z = together_; z < 8; ++z) {
                    cube.lock();
                    cube.lightLayerZ(z - together_, LED_OFF);
                    cube.setImageInLayerZ(z, image);
                    cube.unlock();
                    sleepMs(interval1_);
                }
            }
            break;
        default:
            break;
        }

        sleepMs(interval2_ / 3);
    } // end for ch

    Call(cube.clear());
}

