#pragma once
#include "effect.h"
#include "../utility/intervals.h"
#include <vector>


class RandomLightEffect :
    public Effect,
    public Interval
{
public:
    void setCount(int count) {
        count_ = count;
    }

    void setStates(const std::vector<int>& states) {
        states_ = states;
    }

public:
    virtual void show();

private:
    int count_ = 256;
    std::vector<int> states_;
};
