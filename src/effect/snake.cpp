#include "./snake.h"
#include "../utility/utils.h"

void SnakeEffect::Snake::init(const std::deque<Coordinate>& coords) {
    this->coords = coords;
    for (auto& coord : coords)
        cube(coord) = LED_ON;
}

void SnakeEffect::Snake::add(const Coordinate& coord) {
    if (coord.isValid()) {
        coords.push_front(coord);
        cube(coord) = LED_ON;
    }
}


void SnakeEffect::Snake::move(Direction direction, bool removeBack) {
    if (removeBack) {
        cube(coords.back()) = LED_OFF;
        coords.pop_back();
    }
    auto newCoord = coords.front().offset(direction, 1);
    if (newCoord.isValid())  {
        coords.push_front(newCoord);
        cube(coords.front()) = LED_ON;
    }
}

void SnakeEffect::show() {
    for (auto& event : events_) {
        cube.clear();
        show(event.xDirection, event.yDirection, event.zDirection,
                event.length, event.interval1, event.interval2);
    }
}

void SnakeEffect::show(Direction xDirection, Direction yDirection, Direction zDirection,
        int length, int interval1, int interval2)
{
    using Vertex = Coordinate;
    Snake snake;

    Direction directions[3] = { xDirection, yDirection, zDirection };

    if (xDirection == X_ASCEND) {
        if (yDirection == Y_ASCEND) {
            if (zDirection == Z_ASCEND) {
                snake.add(0, 0, 0);
            }
            else {
                snake.add(0, 0, 7);
            }
        }
        else if (yDirection == Y_DESCEND) {
            if (zDirection == Z_ASCEND) {
                snake.add(0, 7, 0);
            }
            else {
                snake.add(0, 7, 7);
            }
        }
    }
    else if (xDirection == X_DESCEND) {
        if (yDirection == Y_ASCEND) {
            if (zDirection == Z_ASCEND) {
                snake.add(7, 0, 0);
            }
            else {
                snake.add(7, 0, 7);
            }
        }
        else if (yDirection == Y_DESCEND) {
            if (zDirection == Z_ASCEND) {
                snake.add(7, 7, 0);
            }
            else {
                snake.add(7, 7, 7);
            }
        }
    }

    cube.update();
    sleepMs(interval1);
    for (int i = 0; i < length - 1; ++i) {
        snake.move(directions[i % 3], false);
        cube.update();
        sleepMs(interval1);
    }
    for (int i = length - 1; i < 21 + length; ++i) {
        snake.move(directions[i % 3]);
        cube.update();
        sleepMs(interval1);
    }
}


bool SnakeEffect::readFromFP(FILE* fp) {
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
                    int length, interval1, interval2;

                    fscanf(fp, "%s %s %s %d %d %d",
                            xDirection, yDirection, zDirection,
                            &length, &interval1, &interval2);

                    events_.emplace_back(
                            util::getDirection(xDirection), util::getDirection(yDirection),
                            util::getDirection(zDirection),  
                            length, interval1, interval2);
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


