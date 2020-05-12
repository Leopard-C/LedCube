#include "./breath_cube.h"
#include "../utility/utils.h"

void BreathCubeEffect::show() {
    for (auto& event : events_) {
        show(event.A, event.B, event.fillType, event.count,
                event.interval1, event.interval2);
    }
}

void BreathCubeEffect::show(const Coordinate& A, const Coordinate& B,
        FillType fillType, int count, int interval1, int interval2)
{
    Call(cube.clear());

    cube.setLoopCount(8);
    cube.lightCube(A, B, fillType);
    cube.update();
    for (int k = 0; k < count; ++k) {
        for (int i = 8; i < 80; ++i) {
            cube.setLoopCount(i);
            sleepMs(interval1);
        }
        for (int i = 80; i > 7; --i) {
            cube.setLoopCount(i);
            sleepMs(interval1);
        }
    }

    sleepMs(interval2);
    cube.setLoopCount(0);
    Call(cube.clear());
}


bool BreathCubeEffect::readFromFP(FILE* fp) {
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
                    int x1, y1, z1, x2, y2, z2;
                    char fillType[16] = { 0 };
                    int count, interval1, interval2;
                    fscanf(fp, "%d %d %d %d %d %d %s %d %d %d",
                            &x1, &y1, &z1, &x2, &y2, &z2, fillType,
                            &count, &interval1, &interval2);
                    events_.emplace_back(Coordinate(x1, y1, x1), Coordinate(x2, y2, z2),
                            util::getFillType(fillType),
                            count, interval1, interval2);
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



