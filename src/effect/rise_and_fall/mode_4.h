#pragma once
#include "../effect.h"


class RiseAndFallMode4Effect : public Effect {
public:
    struct Event {
        Event(Layer layer, int interval1, int interval2, int interval3) :
            layer(layer),  interval1(interval1),
            interval2(interval2), interval3(interval3) {}
        Layer layer;
        int interval1;  
        int interval2;
        int interval3;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }
    
    virtual void show();

    virtual bool readFromFP(FILE* fp);

private:
    void show(Layer layer, int interval1, int interval2, int interval3);

private:
    std::vector<Event> events_;
};

