#pragma once
#include "cube.h"


namespace ext {

enum {
    Fill_Hollow = 0,
    Fill_Solid  = 1
};

using Vertex = Coordinate;
void lightCube(const Vertex& A, const Vertex& B, int fill);


} // namespace ext

