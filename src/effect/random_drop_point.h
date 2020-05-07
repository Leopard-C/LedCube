#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include "../utility/intervals.h"
#include <vector>

class RandomDropPointEffect :
    public Effect,
    public Directions,
    public IntervalsPair
{
public:
    virtual void show();

private:
    void show(Direction direction);
};
