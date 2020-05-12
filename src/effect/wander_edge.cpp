#include "./wander_edge.h"
#include "../utility/snake.h"
#include "../utility/utils.h"


void WanderEdgeEffect::show() {
    for (auto& event: events_) {
        show(event.together, event.maxVertexCount, event.interval1, event.interval2);
    }
}

void WanderEdgeEffect::show(int together, int maxVertexCount, int interval1, int interval2) {
    Call(cube.clear());

    Snake snake;
    Direction currDirection = X_ASCEND;
    Direction candidate[2];

    for (int i = 0; i < together; ++i) {
        snake.add(i, 0, 0);
    }

    int vertexCount = 0;

    while (true) {
        bool flag = false;

        if ((currDirection == X_ASCEND && snake.headX() == 7) ||
                (currDirection == X_DESCEND && snake.headX() == 0))
        {
            candidate[0] = snake.headY() == 0 ? Y_ASCEND : Y_DESCEND;
            candidate[1] = snake.headZ() == 0 ? Z_ASCEND : Z_DESCEND;
            flag = true;
        }
        else if ((currDirection == Y_ASCEND && snake.headY() == 7) ||
                (currDirection == Y_DESCEND && snake.headY() == 0))
        {
            candidate[0] = snake.headX() == 0 ? X_ASCEND : X_DESCEND;
            candidate[1] = snake.headZ() == 0 ? Z_ASCEND : Z_DESCEND;
            flag = true;
        }
        else if ((currDirection == Z_ASCEND && snake.headZ() == 7) ||
                (currDirection == Z_DESCEND && snake.headZ() == 0))
        {
            candidate[0] = snake.headX() == 0 ? X_ASCEND : X_DESCEND;
            candidate[1] = snake.headY() == 0 ? Y_ASCEND : Y_DESCEND;
            flag = true;
        }

        if (flag) {
            currDirection = candidate[rand() % 2];
            if ((++vertexCount) > maxVertexCount) {
                break;
            }
        }

        snake.move(currDirection);
        snake.update();
        sleepMs(interval1);
    }

    sleepMs(interval2);
    Call(cube.clear());
}


bool WanderEdgeEffect::readFromFP(FILE* fp) {
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
                    int together, maxVertexCount;
                    int interval1, interval2;
                    fscanf(fp, "%d %d %d %d", &together, &maxVertexCount, &interval1, &interval2);
                    events_.emplace_back(together, maxVertexCount,
                            interval1, interval2);
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




