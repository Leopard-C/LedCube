#pragma once

#include "./effect.h"
#include "../utility/directions.h"
#include <vector>

class LayerScanEffect :
    public Effect,
    public Directions
{
public:
    void setInterval(int interval1, int interval2) {
        interval1_ = interval1;
        interval2_ = interval2;
    }

protected:
    virtual void show();

private:
    int interval1_ = 50;
    int interval2_ = 50;
};
