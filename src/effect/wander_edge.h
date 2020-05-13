#pragma once
#include "./effect.h"


class WanderEdgeEffect : public Effect {
public:
    struct Event {
        Event(int together, int maxVertexCount, int interval1, int interval2) :
            together(together), maxVertexCount(maxVertexCount),
            interval1(interval1), interval2(interval2) 
        {
            if (together > 7) {
                this->together = 7;
            }
        }
        int together;
        int maxVertexCount;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(int together, int maxVertexCount, int interval1, int interval2);

private:
    std::vector<Event> events_;
};

