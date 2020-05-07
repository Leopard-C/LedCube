#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include "../utility/intervals.h"
#include <string>


class DropTextPointEffect :
    public Effect,
    public DirectionsAnglePair,
    public IntervalsPair
{
public:
    void setString(const std::string& str);

    void setRotate(Angle rotate) {
        rotate_ = rotate;
    }

protected:
    virtual void show();

private:
    void show(Direction direction, Direction subDirection, Angle angle);

private:
    std::string string_;
    Angle rotate_ = ANGLE_0;
};
