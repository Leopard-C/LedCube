#pragma once
#include "./effect.h"
#include "../utility/directions.h"
#include "../utility/intervals.h"

enum ChangeType {
    SmallToBig = 0,
    BigToSmall = 1,
};


class CubeSizeEffect :
    public Effect,
    public DirectionsTri,
    public IntervalsPair
{
public:
    virtual void show();

    void setChangesType(const std::vector<ChangeType>& changesType) {
        changesType_ = changesType;
    }
    
    void emplaceChangeType(ChangeType type) {
        changesType_.push_back(type);
    }

private:
    void show(Direction directionx, Direction directiony, Direction directionz, ChangeType changeType);

private:
    std::vector<Direction>& directionsx_= directions1_;
    std::vector<Direction>& directionsy_= directions2_;
    std::vector<Direction>& directionsz_= directions3_;
private:
    std::vector<ChangeType> changesType_;
};


