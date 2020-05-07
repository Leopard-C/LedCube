#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include "../utility/intervals.h"
#include <vector>

class DropPointEffect :
    public Effect,
    public DirectionsPair,
    public IntervalsPair
{
protected:
    virtual void show();

private:
    void show(Direction direction, Direction subDirection);
};
