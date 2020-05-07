#include "cube_size.h"
#include "../driver/cube_extend.h"

extern LedCube cube;


void CubeSizeEffect::show() {
    if (directionsx_.size() != directionsy_.size() ||
        directionsx_.size() != directionsz_.size() ||
        directionsx_.size() != changesType_.size())
        return;

    int size = directionsx_.size();

    for (int i = 0; i < size; ++i) {
        show(directionsx_[i], directionsy_[i], directionsz_[i], changesType_[i]);
        sleepMs(interval2_);
    }
}

void CubeSizeEffect::show(Direction directionx, Direction directiony, Direction directionz, ChangeType changeType) {
    using Vertex = Coordinate;
    Vertex fixVertex;
    if (directionx == X_ASCEND) {
        if (directiony == Y_ASCEND) {
            if (directionz == Z_ASCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 0, 0, 0 };
                }
                else {
                    fixVertex = { 7, 7, 7 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {i, i, i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (directionz == Z_DESCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 0, 0, 7 };
                }
                else {
                    fixVertex = { 7, 7, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {i, i, 7-i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
        }
        else if (directiony == Y_DESCEND) {
            if (directionz == Z_ASCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 0, 7, 0 };
                }
                else {
                    fixVertex = { 7, 0, 7 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {i, 7-i, i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (directionz == Z_DESCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 0, 7, 7 };
                }
                else {
                    fixVertex = { 7, 0, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {i, 7-i, 7-i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
        }
    }
    else if (directionx == X_DESCEND) {
        if (directiony == Y_ASCEND) {
            if (directionz == Z_ASCEND) {
                for (int i = 0; i < 8; ++i) {
                    if (changeType == SmallToBig) {
                        fixVertex = { 7, 0, 0 };
                    }
                    else {
                        fixVertex = { 0, 7, 7 };
                    }
                    cube.clear();
                    ext::lightCube(fixVertex, {7-i, i, i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (directionz == Z_DESCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 7, 0, 7 };
                }
                else {
                    fixVertex = { 0, 7, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {7-i, i, 7-i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
        }
        else if (directiony == Y_DESCEND) {
            if (directionz == Z_ASCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 7, 7, 0 };
                }
                else {
                    fixVertex = { 0, 0, 7 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {7-i, 7-i, i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
            else if (directionz == Z_DESCEND) {
                if (changeType == SmallToBig) {
                    fixVertex = { 7, 7, 7 };
                }
                else {
                    fixVertex = { 0, 0, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    ext::lightCube(fixVertex, {7-i, 7-i, 7-i}, ext::Fill_Hollow);
                    cube.update();
                    sleepMs(interval1_);
                }
            }
        }
    }
}
