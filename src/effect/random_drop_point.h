#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include <vector>

class RandomDropPointEffect :
    public Effect,
    public Directions
{
public:
    void setInterval(int interval) {
        interval_ = interval;
    }

    void pause() {
        sleepMs(interval_);
    }

protected:
    virtual void show();

private:
    void show(Direction direction);

private:
    int interval_ = 30;
};
