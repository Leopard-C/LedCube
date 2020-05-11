#pragma once
#include "./effect.h"
#include <vector>

class DropLineEffect : public Effect
{
public:
    struct Event {
        Event(Direction view, Direction drop, Direction parallel, Angle rotate,
                int together, int interval1, int interval2) :
                    viewDirection(view), dropDirection(drop), parallel(parallel),
                    rotate(rotate), interval1(interval1), interval2(interval2)
        {
            if (together < 1 || together > 6) {
                this->together = 1;
            }
            else {
                this->together = together;
            }
        }
        Direction viewDirection;
        Direction dropDirection;
        Direction parallel;
        Angle rotate;
        int together;
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

    void show(int imageCode, Direction viewDirection, Direction scanDirection, Direction parallel,
            Angle rotate, int together, int interval1, int interval2);

private:
    std::vector<int> imagesCode_;
    std::vector<Event> events_;
};
