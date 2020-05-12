#pragma once
#include "cube.h"


namespace ext {

using Vertex = Coordinate;

void lightCube(const Vertex& A, const Vertex& B, FillType fill);
void lightSqure(const Vertex& A, const Vertex& B, FillType fill);

void lightCircleInLayerX(int x, int diameter, FillType fill);
void lightCircleInLayerY(int y, int diameter, FillType fill);
void lightCircleInLayerZ(int z, int diameter, FillType fill);

void getFrameOfFunction(std::string func, char buff[][8][8]);

} // namespace ext

