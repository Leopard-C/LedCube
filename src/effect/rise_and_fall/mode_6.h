#pragma once
#include "./mode_5.h"


class RiseAndFallMode6Effect : public RiseAndFallMode5Effect {
private:
    virtual void showLayerXorYorZ(Layer layer, int count, int interval1, int interval2);
    virtual void showLayerXY(Layer layer, int count, int interval1, int interval2);

private:
    std::vector<Event> events_;
};

