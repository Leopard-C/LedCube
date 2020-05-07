#include "drop_point.h"

void DropPointEffect::show() {
    if (subDirections_.size() != directions_.size())
        return;

    int size = directions_.size();
    for (int i = 0; i < size; ++i) {
        show(directions_[i], subDirections_[i]);
        sleepMs(interval2_);
    }
}

void DropPointEffect::show(Direction direction, Direction subDirection) {
    switch(direction) {
    case X_ASCEND:
        if (subDirection == PARALLEL_Y) {
            Call(cube.clear());
            Call(cube.lightLayerX(0, LED_ON));
            sleepMs(interval1_);
            for (int z = 0; z < 8; ++z) {
                for (int y = 0; y < 8; ++y) {
                    for (int x = 1; x < 8; ++x) {
                        cube(x - 1, y, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        else if (subDirection == PARALLEL_Z) {
            Call(cube.clear());
            Call(cube.lightLayerX(0, LED_ON));
            sleepMs(interval1_);
            for (int y = 0; y < 8; ++y) {
                for (int z = 0; z < 8; ++z) {
                    for (int x = 1; x < 8; ++x) {
                        cube(x - 1, y, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        break;
    case X_DESCEND:
        if (subDirection == PARALLEL_Y) {
            Call(cube.clear());
            Call(cube.lightLayerX(7, LED_ON));
            sleepMs(interval1_);
            for (int z = 0; z < 8; ++z) {
                for (int y = 0; y < 8; ++y) {
                    for (int x = 6; x > -1; --x) {
                        cube(x + 1, y, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        else if (subDirection == PARALLEL_Z) {
            Call(cube.clear());
            Call(cube.lightLayerX(7, LED_ON));
            sleepMs(interval1_);
            for (int y = 0; y < 8; ++y) {
                for (int z = 0; z < 8; ++z) {
                    for (int x = 6; x > -1; --x) {
                        cube(x + 1, y, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
            break;
        }
    case Y_ASCEND:
        if (subDirection == PARALLEL_X) {
            Call(cube.clear());
            Call(cube.lightLayerY(0, LED_ON));
            sleepMs(interval1_);
            for (int z = 0; z < 8; ++z) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 1; y < 8; ++y) {
                        cube(x, y - 1, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        else if (subDirection == PARALLEL_Z) {
            Call(cube.clear());
            Call(cube.lightLayerY(0, LED_ON));
            sleepMs(interval1_);
            for (int x = 0; x < 8; ++x) {
                for (int z = 0; z < 8; ++z) {
                    for (int y = 1 ; y < 8; ++y) {
                        cube(x, y - 1, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        break;
    case Y_DESCEND:
        if (subDirection == PARALLEL_X) {
            Call(cube.clear());
            Call(cube.lightLayerY(7, LED_ON));
            sleepMs(interval1_);
            for (int z = 0; z < 8; ++z) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 6; y > -1; --y) {
                        cube(x, y + 1, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        else if (subDirection == PARALLEL_Z) {
            Call(cube.clear());
            Call(cube.lightLayerY(7, LED_ON));
            sleepMs(interval1_);
            for (int x = 0; x < 8; ++x) {
                for (int z = 0; z < 8; ++z) {
                    for (int y = 6 ; y > -1; --y) {
                        cube(x, y + 1, z) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        break;
    case Z_ASCEND:
        if (subDirection == PARALLEL_X) {
            Call(cube.clear());
            Call(cube.lightLayerZ(0, LED_ON));
            sleepMs(interval1_);
            for (int y = 0; y < 8; ++y) {
                for (int x = 0; x < 8; ++x) {
                    for (int z = 1; z < 8; ++z) {
                        cube(x, y, z - 1) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        else if (subDirection == PARALLEL_Y) {
            Call(cube.clear());
            Call(cube.lightLayerZ(0, LED_ON));
            sleepMs(interval1_);
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    for (int z = 1; z < 8; ++z) {
                        cube(x, y, z - 1) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        break;
    case Z_DESCEND:
        if (subDirection == PARALLEL_X) {
            Call(cube.clear());
            Call(cube.lightLayerZ(7, LED_ON));
            sleepMs(interval1_);
            for (int y = 0; y < 8; ++y) {
                for (int x = 0; x < 8; ++x) {
                    for (int z = 6; z > -1; --z) {
                        cube(x, y, z + 1) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        else if (subDirection == PARALLEL_Y) {
            Call(cube.clear());
            Call(cube.lightLayerZ(7, LED_ON));
            sleepMs(interval1_);
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    for (int z = 6; z > -1; --z) {
                        cube(x, y, z + 1) = LED_OFF;
                        cube(x, y, z) = LED_ON;
                        cube.update();
                        sleepMs(interval1_);
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}
