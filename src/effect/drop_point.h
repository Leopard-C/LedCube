#pragma once
#include "./effect.h"
#include <vector>

enum {
    S_Shape = 1
};


class DropPointEffect : public Effect
{
public:
    struct Event {
        Event(Direction view, Direction drop, Direction parallel, Angle rotate,
                bool is_S_Shape, int together, int interval1, int interval2) :
                    viewDirection(view), dropDirection(drop), parallel(parallel),
                    rotate(rotate), is_S_Shape(is_S_Shape),
                    interval1(interval1), interval2(interval2)
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
        bool is_S_Shape;
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

    void emplaceImagesCode(int imageCode) {
        imagesCode_.push_back(imageCode);
    }

    void clearImagesCode() {
        std::vector<int>().swap(imagesCode_);
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(int imageCode, Direction viewDirection, Direction scanDirection, Direction parallel,
            Angle rotate, bool is_S_Shape, int together, int interval1, int interval2);

protected:
    std::vector<int> imagesCode_;
    std::vector<Event> events_;
};

