#pragma once
#include <deque>
#include <vector>
#include "./coordinate.h"


class Snake {
public:
    enum {
        OK = 0,
        END = 1,
        ERROR = 2,
        INVALID_DIRECTION = 3
    };

    void init(const std::deque<Coordinate>& coords);
    int move(Direction direction, bool removeBack = true);

    void add(const Coordinate& coord);
    void add(int x, int y, int z) { add({x, y, z}); };

    const Coordinate& head() const { return coords_.front(); }
    int headX() const { return coords_.front().x; }
    int headY() const { return coords_.front().y; }
    int headZ() const { return coords_.front().z; }

    void update();

    void removeBack();

protected:
    std::deque<Coordinate> coords_;
};


class NavigateSnakeAutoLength : public Snake {
public:
    int move();
    int smartMove();

    void setLength(int len) {
        length_ = len > 0 ? len : 1;
    }

    void setDirections(const std::vector<Direction>& directions) {
        directions_ = directions;
    }

private:
    int directionIdx = -1;
    int length_ = 0;
    std::vector<Direction> directions_;
    bool hasComeOut = false;
    bool isDisapperaing = false;
};


class NavigateSnakeAutoIncreace : public Snake {
public:
    int move();

    void setDirections(const std::vector<Direction>& directions) {
        directions_ = directions;
    }

private:
    int directionIdx = -1;
    std::vector<Direction> directions_;
};

