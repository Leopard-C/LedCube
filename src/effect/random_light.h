#pragma once
#include "effect.h"
#include "../utility/intervals.h"
#include <vector>


class RandomLightEffect :
    public Effect,
    public Interval
{
public:
    struct Event {
        Event(LedState state, int together, int maxNum, int interval1, int interval2) :
                state(state), interval1(interval1), interval2(interval2)
        {
            if (together < 0)
                this->together = 1;
            else if (together > 256)
                this->together = 256;
            else
                this->together = together;

            if (maxNum < 0)
                this->maxNum = 1;
            else if (maxNum > 512)
                this->maxNum = 512;
            else
                this->maxNum = maxNum;
        }
        LedState state;
        char null[3];
        int together;
        int maxNum;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

private:
    std::vector<Event> events_;
};
