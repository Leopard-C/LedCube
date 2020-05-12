#pragma once
#include "../effect.h"


class RiseAndFallMode1Effect : public Effect {
public:
    struct Event {
        Event(int count, int interval1, int interval2) :
            count(count), interval1(interval1), interval2(interval2) {}
        int count;
        int interval1;     
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }
    
    virtual void show();

    virtual bool readFromFP(FILE* fp);

protected:
    virtual void rise(int interval1);
    virtual void fall(int interval1);

private:
    std::vector<Event> events_;
};
