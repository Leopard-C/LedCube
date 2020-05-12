#pragma once
#include "./mode_1.h"


class RiseAndFallMode2Effect : public RiseAndFallMode1Effect {
protected:
    virtual void rise(int interval);
    virtual void fall(int interval);
};
