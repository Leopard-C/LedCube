#pragma once
#include <vector>

enum Direction {
    X_ASCEND  = 0,
    X_DESCEND = 1,
    Y_ASCEND  = 2,
    Y_DESCEND = 3,
    Z_ASCEND  = 4,
    Z_DESCEND = 5,
PARALLEL_X = 10,
    PARALLEL_Y = 11,
    PARALLEL_Z = 12
}; enum Angle { ANGLE_0   = 0,
    ANGLE_90  = 90,
    ANGLE_180 = 180,
    ANGLE_270 = 270
};

class Directions {
public:
    void clearDirections() {
        std::vector<Direction>().swap(directions_);
    }

    void setDirections(const std::vector<Direction>& directions) {
        directions_ = directions;
    }

    void emplaceDirection(Direction direction) {
        directions_.push_back(direction);
    }

protected:
    std::vector<Direction> directions_;
};


class DirectionsPair {
public:
    void clear() {
        std::vector<Direction>().swap(directions_);
        std::vector<Direction>().swap(subDirections_);
    }

    void setDirections(const std::vector<Direction>& directions,
            const std::vector<Direction>& subDirections) {
        directions_ = directions;
        subDirections_ = subDirections;
    }

    void emplaceDirection(Direction direction, Direction subDirection) {
        directions_.push_back(direction);
        subDirections_.push_back(subDirection);
    }

protected:
    std::vector<Direction> directions_;
    std::vector<Direction> subDirections_;
};


class DirectionsTri {
public:
    void clear() {
        std::vector<Direction>().swap(directions1_);
        std::vector<Direction>().swap(directions2_);
        std::vector<Direction>().swap(directions3_);
    }

    void setDirections(const std::vector<Direction>& directions1,
            const std::vector<Direction>& directions2,
            const std::vector<Direction>& directions3) {
        directions1_ = directions1;
        directions2_ = directions2;
        directions3_ = directions3;
    }

    void emplaceDirection(Direction direction1, Direction direction2, Direction direction3) {
        directions1_.push_back(direction1);
        directions2_.push_back(direction2);
        directions3_.push_back(direction3);
    }

protected:
    std::vector<Direction> directions1_;
    std::vector<Direction> directions2_;
    std::vector<Direction> directions3_;
};


class DirectionsAnglePair {
public:
    void clearDirections() {
        std::vector<Direction>().swap(directions_);
        std::vector<Direction>().swap(subDirections_);
        std::vector<Angle>().swap(angles_);
    }

    void setDirectionsAngles(const std::vector<Direction>& directions,
            const std::vector<Direction>& subDirections,
            const std::vector<Angle>& angles) {
        directions_ = directions;
        subDirections_ = subDirections;
        angles_ = angles;
    }

    void emplaceDirectionAngle(Direction direction, Direction subDirection, Angle angle) {
        directions_.push_back(direction);
        subDirections_.push_back(subDirection);
        angles_.push_back(angle);
    }

protected:
    std::vector<Direction> directions_;
    std::vector<Direction> subDirections_;
    std::vector<Angle> angles_;
};


