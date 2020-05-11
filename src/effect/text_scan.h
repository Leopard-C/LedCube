#pragma once

#include "./layer_scan.h"
#include <string>
#include <vector>


class TextScanEffect : public LayerScanEffect
{
public:
    void setText(std::string text);     // not use const reference

    virtual bool readFromFP(FILE* fp);
};

