#pragma once
#include "./drop_point.h"


class DropTextPointEffect : public DropPointEffect {
public:
    void setText(const std::string& str);

public:
    virtual bool readFromFP(FILE* fp);

private:
    std::string string_;
};

