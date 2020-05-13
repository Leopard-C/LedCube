#pragma once
#include "./effect.h"


class BreathCubeEffect : public Effect {
public:
    struct Event {
        Event(const Coordinate& A, const Coordinate& B, FillType fillType,
                int count, int interval1, int interval2) :
            A(A), B(B), fillType(fillType), count(count),
            interval1(interval1), interval2(interval2) {}
        Coordinate A;
        Coordinate B;
        FillType fillType;
        int count;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(const Coordinate& A, const Coordinate& B, FillType fillType,
            int count, int interval1, int interval2);

private:
    std::vector<Event> events_;
};

