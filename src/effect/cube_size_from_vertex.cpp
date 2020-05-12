#include "cube_size_from_vertex.h"
#include "../driver/cube_extend.h"
#include "../utility/utils.h"

extern LedCube cube;


void CubeSizeFromVertexEffect::show() {
    for (auto& event : events_) {
        show(event.xDirection, event.yDirection, event.zDirection, event.changeType,
                event.fillType, event.interval1, event.interval2);
    }
}

void CubeSizeFromVertexEffect::show(Direction xDirection, Direction yDirection, Direction zDirection,
        ChangeType changeType, FillType fillType, int interval1, int interval2)
{
    using Vertex = Coordinate;
    Vertex fixVertex;
    if (xDirection == X_ASCEND) {
        if (yDirection == Y_ASCEND) {
            if (zDirection == Z_ASCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 0, 0, 0 };
                }
                else {
                    fixVertex = { 7, 7, 7 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {i, i, i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
            else if (zDirection == Z_DESCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 0, 0, 7 };
                }
                else {
                    fixVertex = { 7, 7, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {i, i, 7-i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }
        else if (yDirection == Y_DESCEND) {
            if (zDirection == Z_ASCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 0, 7, 0 };
                }
                else {
                    fixVertex = { 7, 0, 7 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {i, 7-i, i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
            else if (zDirection == Z_DESCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 0, 7, 7 };
                }
                else {
                    fixVertex = { 7, 0, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {i, 7-i, 7-i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }
    }
    else if (xDirection == X_DESCEND) {
        if (yDirection == Y_ASCEND) {
            if (zDirection == Z_ASCEND) {
                for (int i = 0; i < 8; ++i) {
                    if (changeType == SMALL_TO_BIG) {
                        fixVertex = { 7, 0, 0 };
                    }
                    else {
                        fixVertex = { 0, 7, 7 };
                    }
                    cube.clear();
                    cube.lightCube(fixVertex, {7-i, i, i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
            else if (zDirection == Z_DESCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 7, 0, 7 };
                }
                else {
                    fixVertex = { 0, 7, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {7-i, i, 7-i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }
        else if (yDirection == Y_DESCEND) {
            if (zDirection == Z_ASCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 7, 7, 0 };
                }
                else {
                    fixVertex = { 0, 0, 7 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {7-i, 7-i, i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
            else if (zDirection == Z_DESCEND) {
                if (changeType == SMALL_TO_BIG) {
                    fixVertex = { 7, 7, 7 };
                }
                else {
                    fixVertex = { 0, 0, 0 };
                }
                for (int i = 0; i < 8; ++i) {
                    cube.clear();
                    cube.lightCube(fixVertex, {7-i, 7-i, 7-i}, fillType);
                    cube.update();
                    sleepMs(interval1);
                }
            }
        }
    }

    sleepMs(interval2);
}


bool CubeSizeFromVertexEffect::readFromFP(FILE* fp) {
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
                    char xDirection[12] = { 0 };
                    char yDirection[12] = { 0 };
                    char zDirection[12] = { 0 };
                    char changeType[16] = { 0 };
                    char fillType[16] = { 0 };
                    int interval1, interval2;

                    fscanf(fp, "%s %s %s %s %s %d %d",
                            xDirection, yDirection, zDirection,
                            changeType, fillType, &interval1, &interval2);

                    events_.emplace_back(
                            util::getDirection(xDirection), util::getDirection(yDirection),
                            util::getDirection(zDirection), util::getChangeType(changeType),
                            util::getFillType(fillType), interval1, interval2);
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

