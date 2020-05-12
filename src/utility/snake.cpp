#include "./snake.h"
#include "../driver/cube.h"

extern LedCube cube;


void Snake::init(const std::deque<Coordinate>& coords) {
    coords_ = coords;
    for (auto& coord : coords_)
        cube(coord) = LED_ON;
}

void Snake::add(const Coordinate& coord) {
    if (coord.isValid()) {
        coords_.push_front(coord);
        cube(coord) = LED_ON;
    }
}

void Snake::update() {
    cube.update();
}


int Snake::move(Direction direction, bool removeBack) {
    auto newCoord = coords_.front().getOffset(direction, 1);
    if (newCoord.isValid()) {
        coords_.push_front(newCoord);
        cube(coords_.front()) = LED_ON;
        if (removeBack) {
            cube(coords_.back()) = LED_OFF;
            coords_.pop_back();
        }
        return Snake::OK;
    }
    else {
        return Snake::INVALID_DIRECTION;
    }
}

void Snake::removeBack() {
    cube(coords_.back()) = LED_OFF;
    coords_.pop_back();
}



int NavigateSnakeAutoLength::move() {
    if (coords_.empty())
        return Snake::ERROR;
    if (directionIdx == -1) {
        if (directions_.empty())
            return Snake::ERROR;
        else
            directionIdx = 0;
    }
    if (Snake::move(directions_[directionIdx]) == Snake::INVALID_DIRECTION) {
        if (directionIdx + 1 < directions_.size())
            ++directionIdx;
        else
            return Snake::END;

        if (Snake::move(directions_[directionIdx]) == Snake::INVALID_DIRECTION)
            return Snake::ERROR;
    }
    return Snake::OK;
}


int NavigateSnakeAutoLength::smartMove() {
    if (directionIdx == -1) {
        if (directions_.empty())
            return Snake::ERROR;
        else
            directionIdx = 0;
    }

    int currLen = coords_.size();
    if (currLen == 0)
        return Snake::ERROR;
    else if (currLen > length_)
        return Snake::ERROR;
    else if (currLen < length_) {
        if (!hasComeOut) {
            int ret = Snake::move(directions_[directionIdx], false);
            if (ret == Snake::OK)
                return Snake::OK;
            else
                return Snake::ERROR;
        }
        else if (isDisapperaing) {
            cube(coords_.back()) = LED_OFF;
            coords_.pop_back();
            if (coords_.empty())
                return Snake::END;
            else
                return Snake::OK;
        }
        else {
            // won't get down here
            return Snake::ERROR;
        }
    }
    else {
        hasComeOut = true;
        int ret = NavigateSnakeAutoLength::move();
        if (ret == Snake::END) {
            isDisapperaing = true;
            cube(coords_.back()) = LED_OFF;
            coords_.pop_back();
            return Snake::OK;
        }
        else {
            return ret;
        }
    }
}


int NavigateSnakeAutoIncreace::move() {
    if (coords_.empty())
        return Snake::ERROR;
    if (directionIdx == -1) {
        if (directions_.empty())
            return Snake::ERROR;
        else
            directionIdx = 0;
    }
    if (Snake::move(directions_[directionIdx], false) == Snake::INVALID_DIRECTION) {
        if (directionIdx + 1 < directions_.size())
            ++directionIdx;
        else
            return Snake::END;

        if (Snake::move(directions_[directionIdx], false) == Snake::INVALID_DIRECTION)
            return Snake::ERROR;
    }
    return Snake::OK;
}

