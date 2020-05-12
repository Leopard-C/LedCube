#pragma once
#include "../effect.h"


class RiseAndFallMode5Effect : public Effect {
public:
    struct Event {
        Event(Layer layer, int count, int interval1, int interval2) :
            layer(layer), count(count), 
            interval1(interval1), interval2(interval2) {}
        Layer layer;
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
    virtual void showLayerXorYorZ(Layer layer, int count, int interval1, int interval2);
    virtual void showLayerXY(Layer layer, int count, int interval1, int interval2);
    void lightXY45(int c, int z, LedState state);
    void lightXY135(int c, int z, LedState state);

private:
    std::vector<Event> events_;
};

