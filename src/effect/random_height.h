#pragma once
#include "./effect.h"

class RandomHeightEffect : public Effect {
public:
    struct Event {
        Event(int together, ShapeType shape, int duration, int interval1, int interval2) :
            together(together), shape(shape),
            duration(duration), interval1(interval1), interval2(interval2) {}
        int together;
        ShapeType shape;
        int duration;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

    virtual void show();
    virtual bool readFromFP(FILE* fp);

private:
    void show(int together, ShapeType shape, int duration, int interval1, int interval2);

private:
    std::vector<Event> events_;
};
