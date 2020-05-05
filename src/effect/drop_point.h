#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include <vector>

class DropPointEffect :
    public Effect,
    public DirectionsPair
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
    void show(Direction direction, Direction subDirection);

private:
    int interval_ = 50;
};
