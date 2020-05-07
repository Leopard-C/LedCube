#pragma once

#include "./layer_scan.h"
#include <string>


class TextScanEffect :
    public LayerScanEffect
{
public:
    void setText(std::string text);     // not use const reference
};

