#pragma once
#include "effect.h"


class RandomLightEffect : public Effect {
public:
    void setInterval(int interval) {
        interval_ = interval;
    }

    void setCount(int count) {
        count_ = count;
    }

protected:
    virtual void show();

private:
    int interval_ = 50;
    int count_ = 256;
};
