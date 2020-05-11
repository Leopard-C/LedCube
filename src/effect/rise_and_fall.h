#pragma once

#include "./effect.h"


class RiseAndFallEffect : public Effect {
public:

    virtual void show();

private:
    void rise(int interval);
    void fall(int interval);

};
