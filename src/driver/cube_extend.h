#pragma once
#include "./cube.h"


namespace ext {

using Vertex = Coordinate;

void lightCircleInLayerX(int x, int diameter, FillType fill);
void lightCircleInLayerY(int y, int diameter, FillType fill);
void lightCircleInLayerZ(int z, int diameter, FillType fill);

void getFrameOfFunction(std::string func, char buff[][8][8]);

void showStringInLayerZ(std::string str, int interval, int z, Direction viewDirection = Z_DESCEND, Angle rotate = ANGLE_0);
void showStringInLayerY(std::string str, int interval, int y, Direction viewDirection = Y_DESCEND, Angle rotate = ANGLE_0);
void showStringInLayerX(std::string str, int interval, int x, Direction viewDirection = X_DESCEND, Angle rotate = ANGLE_0);


} // namespace ext

