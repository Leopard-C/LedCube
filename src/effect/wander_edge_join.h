#pragma once
#include "./effect.h"


class WanderEdgeJoinEffect : public Effect {
public:
    struct Event {
        Event(Direction xDirection, Direction yDirection, Direction zDirection,
                int together, int interval1, int interval2) :
            xDirection(xDirection), yDirection(yDirection), zDirection(zDirection),
            together(together), interval1(interval1), interval2(interval2) 
        {
            if (together > 7) {
                this->together = 7;
            }
        }
        Direction xDirection;
        Direction yDirection;
        Direction zDirection;
        int together;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(Direction xDirection, Direction yDirection, Direction zDirection,
            int together, int interval1, int interval2);

private:
    std::vector<Event> events_;
};

