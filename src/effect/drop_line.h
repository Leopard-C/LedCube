#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include "../utility/intervals.h"
#include <vector>

class DropLineEffect :
    public Effect,
    public DirectionsPair,
    public IntervalsPair
{
public:
    virtual void show();

private:
    void show(Direction direction, Direction subDirection);
};
