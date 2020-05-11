#include "./effect.h"
#include "../driver/cube_extend.h"
#include <vector>


class CubeSizeFromInnerEffect : public Effect
{
public:
    struct Event {
        Event(ChangeType changeType, FillType fillType, int interval1, int interval2) :
                    changeType(changeType), fillType(fillType), interval1(interval1), interval2(interval2) {}
        ChangeType changeType;
        FillType fillType;
        int interval1;
        int interval2;
    };

    void setEvents(const std::vector<Event>& events) {
        events_ = events;
    }

public:
    virtual void show();
    virtual bool readFromFP(FILE* fp);

    void show(ChangeType changeType, FillType fillType,
            int interval1, int interval2);

private:
    std::vector<Event> events_;
};
