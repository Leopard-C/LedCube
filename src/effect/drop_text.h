#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include <string>


class DropTextEffect :
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

    void setTogetherLayers(int together) {
        if (together > 0 && together < 6)
            together_ = together;
        else
            together_ = 1;
    }

protected:
    virtual void show();

private:
    void show(Direction direction, Direction subDirection, Angle angle);

private:
    std::string string_;
    Angle rotate_ = ANGLE_0;
    int interval1_ = 200;
    int interval2_ = 200;
    int together_ = 1;
};
