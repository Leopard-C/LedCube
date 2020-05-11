#pragma once
#include "./effect.h"
#include <vector>


class RandomDropPointEffect : public Effect
{
public:
    struct Event {
        Event(Direction view, Direction drop, Angle rotate,
                int togetherView, int togetherScan,
                int interval1, int interval2) :
            viewDirection(view), dropDirection(drop), rotate(rotate),
            interval1(interval1), interval2(interval2)
        {
            if (togetherScan < 1 || togetherScan > 6)
                this->togetherScan = 1;
            else
                this->togetherScan = togetherScan;
            if (togetherView != 1 && togetherView % 2 != 0)
                this->togetherView = togetherView - 1;
            else
                this->togetherView = togetherView;
        }
        Direction viewDirection;
        Direction dropDirection;
        Angle rotate;
        int togetherView;
        int togetherScan;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

    void setImagesCode(const std::vector<int>& imagesCodeIn) {
        imagesCode_ = imagesCodeIn;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(int imageCode, Direction viewDirection, Direction dropDirection, Angle rotate,
            int togetherView, int togetherScan, int interval1, int interval2);

private:
    std::vector<int> imagesCode_;
    std::vector<Event> events_;
};
