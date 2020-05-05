#include "./drop_text_point.h"
#include "../driver/cube.h"
#include "../utility/image_lib.h"
#include <cstring>
#include <algorithm>

extern LedCube cube;


void DropTextPointEffect::setString(const std::string& str) {
    string_ = str;
    ImageLib::validate(string_);
}

void DropTextPointEffect::show() {
    int size = directions_.size();
    for (int i = 0; i < size; ++i) {
        show(directions_[i], subDirections_[i], angles_[i]);
    }
}

void DropTextPointEffect::show(Direction direction, Direction subDirection, Angle angle) {
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
                Call(cube.setImageInLayerX(0, image));
                sleepMs(interval1_);
                for (int y = 0; y < 8; ++y) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(0, y, z) == LED_ON) {
                            for (int x = 1; x < 8; ++x) {
                                cube.lock();
                                cube(x - 1, y, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            else if (subDirection == X_DESCEND) {
                Call(cube.setImageInLayerX(7, image));
                sleepMs(interval1_);
                for (int y = 0; y < 8; ++y) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(7, y, z) == LED_ON) {
                            for (int x = 6; x > -1; --x) {
                                cube.lock();
                                cube(x + 1, y, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            break;
        case X_DESCEND:
            cube.getImageInLayerX(image, ch, direction, angle);
            if (subDirection == X_DESCEND) {
                Call(cube.setImageInLayerX(7, image));
                sleepMs(interval1_);
                for (int y = 7; y > -1; --y) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(7, y, z) == LED_ON) {
                            for (int x = 6; x > -1; --x) {
                                cube.lock();
                                cube(x + 1, y, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            else if (subDirection == X_ASCEND) {
                Call(cube.setImageInLayerX(0, image));
                sleepMs(interval1_);
                for (int y = 7; y > -1; --y) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(0, y, z) == LED_ON) {
                            for (int x = 1; x < 8; ++x) {
                                cube.lock();
                                cube(x - 1, y, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            break;
        case Y_ASCEND:
            cube.getImageInLayerY(image, ch, direction, angle);
            if (subDirection == Y_ASCEND) {
                Call(cube.setImageInLayerY(0, image));
                sleepMs(interval1_);
                for (int x = 0; x < 8; ++x) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(x, 0, z) == LED_ON) {
                            for (int y = 1; y < 8; ++y) {
                                cube.lock();
                                cube(x, y - 1, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            else if (subDirection == Y_DESCEND) {
                Call(cube.setImageInLayerY(7, image));
                sleepMs(interval1_);
                for (int x = 0; x < 8; ++x) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(x, 7, z) == LED_ON) {
                            for (int y = 6; y > -1; --y) {
                                cube.lock();
                                cube(x, y + 1, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            break;
        case Y_DESCEND:
            cube.getImageInLayerY(image, ch, direction, angle);
            if (subDirection == Y_DESCEND) {
                Call(cube.setImageInLayerY(7, image));
                sleepMs(interval1_);
                for (int x = 0; x < 8; ++x) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(x, 7, z) == LED_ON) {
                            for (int y = 6; y > -1; --y) {
                                cube.lock();
                                cube(x, y + 1, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            else if (subDirection == Y_ASCEND) {
                Call(cube.setImageInLayerY(0, image));
                sleepMs(interval1_);
                for (int x = 0; x < 8; ++x) {
                    for (int z = 7; z > -1; --z) {
                        if (cube(x, 0, z) == LED_ON) {
                            for (int y = 1; y < 8; ++y) {
                                cube.lock();
                                cube(x, y - 1, z) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            break;
        case Z_ASCEND:
            cube.getImageInLayerZ(image, ch, direction, angle);
            if (subDirection == Z_ASCEND) {
                Call(cube.setImageInLayerZ(0, image));
                sleepMs(interval1_);
                for (int y = 0; y < 8; ++y) {
                    for (int x = 0; x < 8; ++x) {
                        if (cube(x, y, 0) == LED_ON) {
                            for (int z = 1; z < 8; ++z) {
                                cube.lock();
                                cube(x, y, z - 1) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            else if (subDirection == Z_DESCEND) {
                Call(cube.setImageInLayerZ(7, image));
                sleepMs(interval1_);
                for (int y = 0; y < 8; ++y) {
                    for (int x = 0; x < 8; ++x) {
                        if (cube(x, y, 7) == LED_ON) {
                            for (int z = 6; z > -1; --z) {
                                cube.lock();
                                cube(x, y, z + 1) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            break;
        case Z_DESCEND:
            cube.getImageInLayerZ(image, ch, direction, angle);
            if (subDirection == Z_DESCEND) {
                Call(cube.setImageInLayerZ(7, image));
                sleepMs(interval1_);
                for (int y = 0; y < 8; ++y) {
                    for (int x = 0; x < 8; ++x) {
                        if (cube(x, y, 7) == LED_ON) {
                            for (int z = 6; z > -1; --z) {
                                cube.lock();
                                cube(x, y, z + 1) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            else if (subDirection == Z_ASCEND) {
                Call(cube.setImageInLayerZ(0, image));
                sleepMs(interval1_);
                for (int y = 0; y < 8; ++y) {
                    for (int x = 0; x < 8; ++x) {
                        if (cube(x, y, 0) == LED_ON) {
                            for (int z = 1; z < 8; ++z) {
                                cube.lock();
                                cube(x, y, z - 1) = LED_OFF;
                                cube(x, y, z) = LED_ON;
                                cube.unlock();
                                sleepMs(interval1_);
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
        }

        sleepMs(interval2_);
    }

    Call(cube.clear());
}

