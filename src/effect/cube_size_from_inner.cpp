#include "./cube_size_from_inner.h"
#include "../driver/cube_extend.h"
#include "../utility/utils.h"


void CubeSizeFromInnerEffect::show() {
    for (auto& event : events_) {
        show(event.changeType, event.fillType, event.interval1, event.interval2);
    }
}

void CubeSizeFromInnerEffect::show(ChangeType changeType, FillType fillType, int interval1, int interval2)
{
    using Vertex = Coordinate;
    if (changeType == SMALL_TO_BIG) {
        for (int i = 0; i < 4; ++i) {
            cube.clear();
            ext::lightCube({3-i, 3-i, 3-i}, {4+i, 4+i, 4+i}, fillType);
            cube.update();
            sleepMs(interval1);
        }
    }
    else if (changeType == BIG_TO_SMALL) {
        for (int i = 0; i < 4; ++i) {
            cube.clear();
            ext::lightCube({i, i, i}, {7-i, 7-i, 7-i}, fillType);
            cube.update();
            sleepMs(interval1);
        }
    }

    sleepMs(interval2);
}

bool CubeSizeFromInnerEffect::readFromFP(FILE* fp) {
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
                    char changeType[16] = { 0 };
                    char fillType[16] = { 0 };
                    int interval1, interval2;
                    fscanf(fp, "%s %s %d %d", changeType, fillType, &interval1, &interval2);
                    events_.emplace_back(util::getChangeType(changeType),
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



