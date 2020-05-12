#pragma once
#include "../effect.h"


class RiseAndFallMode3Effect : public Effect {
public:
    struct Event {
        Event(Layer layer, int param, int count, int interval1, int interval2) :
            layer(layer), param(param), count(count), 
            interval1(interval1), interval2(interval2) {}
        Layer layer;
        int param;  // if layer==Layer_XY45 or Layer_XY135, the param is uselsess.
        int count;
        int interval1;     
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }
    
    virtual void show();

    virtual bool readFromFP(FILE* fp);

private:
    void show(Layer layer, int param, int count, int interval1, int interval2);

private:
    std::vector<Event> events_;
};

