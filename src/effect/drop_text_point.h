#pragma once
#include "./effect.h"
#include "./drop_point.h"
#include <string>


class DropTextPointEffect : public DropPointEffect
{
public:
    void setText(const std::string& str);

public:
    virtual bool readFromFP(FILE* fp);

private:
    std::string string_;
};
