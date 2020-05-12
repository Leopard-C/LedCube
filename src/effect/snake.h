#pragma once
#include "./effect.h"
#include <deque>


class SnakeEffect : public Effect {
public:
    struct Event {
        Event(Direction xDirection, Direction yDirection, Direction zDirection,
                int length, int interval1, int interval2) :
                    xDirection(xDirection), yDirection(yDirection), zDirection(zDirection),
                    length(length), interval1(interval1), interval2(interval2) {}
        Direction xDirection;
        Direction yDirection;
        Direction zDirection;
        int length;
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
            int length, int interval1, int interval2);

private:
    std::vector<Event> events_;
};
