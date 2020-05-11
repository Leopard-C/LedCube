#pragma once
#include "./effect.h"
#include "../utility/image_lib.h"
#include <vector>


class LayerScanEffect : public Effect
{
public:
    class Event {
    public:
        Event(Direction view, Direction scan, Angle r, int together, int interval1, int interval2) :
                viewDirection(view), scanDirection(scan), rotate(r),
                interval1(interval1), interval2(interval2) {
            if (together < 1 || together > 6) {
                this->together = 1;
            }
            else {
                this->together = together;
            }
        }
        Direction viewDirection;
        Direction scanDirection;
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

private:
    void show(int imageCode, Direction viewDirection, Direction scanDirection,
            Angle rotate, int together, int interval1, int interval2);

protected:
    std::vector<int> imagesCode_;
    std::vector<Event> events_;
};

