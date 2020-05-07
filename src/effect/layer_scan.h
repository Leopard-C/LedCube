#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include "../utility/intervals.h"
#include "../utility/image_lib.h"


class LayerScanEffect :
    public Effect,
    public DirectionsAnglePair,
    public IntervalsPair
{
public:
    void setImagesCode(const std::vector<int>& imagesCodeIn) {
        imagesCode_ = imagesCodeIn;
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

public:
    virtual void show();

private:
    void show(Direction direction, Direction subDirection, Angle angle);

private:
    std::vector<int> imagesCode_;
    Angle rotate_ = ANGLE_0;
    int together_ = 1;
};

