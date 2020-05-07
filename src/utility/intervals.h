#pragma once


class Interval {
public:    
    void setInterval(int interval) {
        interval_ = interval;
    }
protected:
    int interval_ = 1;
};


class IntervalsPair {
public:
    void setIntervals(int interval1, int interval2 = 0) {
        interval1_ = interval1;
        interval2_ = interval2;
    }
protected:
    int interval1_ = 1;
    int interval2_ = 0;
};


class IntervalsTri {
public:
    void setIntervals(int interval1, int interval2 = 0, int interval3 = 0) {
        interval1_ = interval1;
        interval2_ = interval2;
        interval3_ = interval3;
    }
protected:
    int interval1_ = 1;
    int interval2_ = 0;
    int interval3_ = 0;
};

