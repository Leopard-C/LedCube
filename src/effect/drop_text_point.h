#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include <string>


class DropTextPointEffect :
    public Effect,
    public DirectionsAnglePair
{
public:
    void setString(const std::string& str);

    void setInterval(int interval1, int interval2) {
        interval1_ = interval1;
        interval2_ = interval2;
    }

    void setRotate(Angle rotate) {
        rotate_ = rotate;
    }

protected:
    virtual void show();

private:
    void show(Direction direction, Direction subDirection, Angle angle);

private:
    std::string string_;
    int interval1_ = 15;
    int interval2_ = 200;
    Angle rotate_ = ANGLE_0;
};
