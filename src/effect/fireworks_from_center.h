#pragma once
#include "./effect.h"


class FireworksFromCenterEffect : public Effect {
public:
    struct Event {
        Event(ShapeType shapeType, FillType fillType,
                int interval1, int interval2, int interval3) :
            shapeType(shapeType), fillType(fillType),
            interval1(interval1), interval2(interval2), interval3(interval3) {}
        ShapeType shapeType;
        FillType fillType;
        int interval1;
        int interval2;
        int interval3;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(ShapeType shapeType, FillType fillType,
            int interval1, int interval2, int interval3);

private:
    std::vector<Event> events_;
};

