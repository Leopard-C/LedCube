#include "utils.h"
#include <map>
#include <algorithm>

namespace util {

bool isNum(const std::string& str) {
    std::stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}

bool isInt(const std::string& str) {
    for (auto c : str) {
        if (c < '0' || c >'9')
            return false;
    }
    return true;
}


void trim(std::string& str) {
    if (str.empty())
        return;
    str.erase(0,str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
}

    
std::vector<int> getRandomArray(int len) {
    std::vector<int> vec;
    vec.reserve(len);
    for (int i = 0; i < len; ++i)
        vec.push_back(i);
    std::random_shuffle(vec.begin(), vec.end());
    return vec;
}

std::vector<int> getRandomArray(int count, int all) {
    std::vector<int> vec;
    vec.reserve(all);
    for (int i = 0; i < all; ++i)
        vec.push_back(i);
    std::random_shuffle(vec.begin(), vec.end());
    return std::vector<int>(vec.begin(), vec.begin() + count);
}


static void toBinary(unsigned char c, std::array<char, 8>& bin) {
    for (int i = 0; i < 8; ++i)
        bin[i] = 0;

    unsigned char i = c;
    int j = 0;
    while (i) {
        bin[j] = i % 2;
        i /= 2;
        j++;
    }

    std::reverse(bin.begin(), bin.end());
}

//
// { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
//      ====>
// {
//   { 1, 1, 1, 1, 1, 1, 1, 1 }
//   { 1, 1, 1, 1, 1, 1, 1, 1 }
//   { 1, 1, 1, 1, 1, 1, 1, 1 }
//   ...
// }
//
std::array<std::array<char, 8>, 8> toBinary(const std::array<unsigned char, 8>& arr) {
    std::array<std::array<char, 8>, 8> retBin;
    for (int i = 0; i < 8; ++i) {
        toBinary(arr[i], retBin[i]);
    }
    return retBin;
}


// Get the column of an image
std::array<char, 8> getCol(const std::array<std::array<char, 8>, 8>& image, int col, bool reverse) {
    std::array<char, 8> colArr;
    if (reverse) {
        for (int row = 0; row < 8; ++row) {
            colArr[row] = image[7-row][col];
        }
    }
    else {
        for (int row = 0; row < 8; ++row) {
            colArr[row] = image[row][col];
        }
    }
    return colArr;
}


static const std::map<std::string, Direction> directionStrMap = {
    { "X_ASCEND", X_ASCEND },
    { "Y_ASCEND", Y_ASCEND },
    { "Z_ASCEND", Z_ASCEND },
    { "X_DESCEND", X_DESCEND },
    { "Y_DESCEND", Y_DESCEND },
    { "Z_DESCEND", Z_DESCEND },
    { "PARALLEL_X", PARALLEL_X },
    { "PARALLEL_Y", PARALLEL_Y },
    { "PARALLEL_Z", PARALLEL_Z }
};

static const std::map<std::string, Angle> angleStrMap = {
    { "ANGLE_0",    ANGLE_0 },
    { "ANGLE_90",   ANGLE_90 },
    { "ANGLE_180",  ANGLE_180 },
    { "ANGLE_2700", ANGLE_270 }
};

static const std::map<std::string, FillType> fillTypeStrMap = {
    { "FILL_EDGE",    FILL_EDGE    },
    { "FILL_SURFACE", FILL_SURFACE },
    { "FILL_SOLID",   FILL_SOLID   }
};

static const std::map<std::string, ChangeType> changeTypeStrMap = {
    { "SMALL_TO_BIG", SMALL_TO_BIG },
    { "BIG_TO_SMALL", BIG_TO_SMALL }
};

static const std::map<std::string, ShapeType> shapeTypeStrMap = {
    { "SHAPE_ERROR", SHAPE_ERROR }, 
    { "POINT",       POINT       },
    { "LINE",        LINE        },
    { "RECTANGLE",   RECTANGLE   },
    { "TRIANGLE",    TRIANGLE    },
    { "CIRCLE",      CIRCLE      },
};

static const std::map<std::string, Layer> layerStrMap = {
    { "LAYER_ERROR", LAYER_ERROR },
    { "LAYER_X",     LAYER_X },
    { "LAYER_Y",     LAYER_Y },
    { "LAYER_Z",     LAYER_Z },
    { "LAYER_XY45",  LAYER_XY45  },
    { "LAYER_XY135", LAYER_XY135 }
};


void toUpperCase(char* str, int len) {
    for (int i = 0; i < len; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void toUpperCase(std::string& str) {
    for (auto& ch : str) {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
    }
}


Direction getDirection(std::string dirStr) {
    toUpperCase(dirStr);
    auto it = directionStrMap.find(dirStr);
    if (it == directionStrMap.end())
        return DIR_ERROR;
    else
        return it->second;
}

Angle getAngle(std::string angleStr) {
    toUpperCase(angleStr);
    auto it = angleStrMap.find(angleStr);
    if (it == angleStrMap.end())
        return ANGLE_ERROR;
    else
        return it->second;
}

ChangeType getChangeType(std::string changeTypeStr) {
    toUpperCase(changeTypeStr);
    auto it = changeTypeStrMap.find(changeTypeStr);
    if (it == changeTypeStrMap.end())
        return CHANGETYPE_ERROR;
    else
        return it->second;
}

FillType getFillType(std::string fillTypeStr) {
    toUpperCase(fillTypeStr);
    auto it = fillTypeStrMap.find(fillTypeStr);
    if (it == fillTypeStrMap.end())
        return CUBEFILL_ERROR;
    else
        return it->second;
}

ShapeType getShape(std::string shapeStr) {
    toUpperCase(shapeStr);
    auto it = shapeTypeStrMap.find(shapeStr);
    if (it == shapeTypeStrMap.end())
        return SHAPE_ERROR;
    else
        return it->second;
}

Layer getLayer(std::string layerStr) {
    toUpperCase(layerStr);
    auto it = layerStrMap.find(layerStr);
    if (it == layerStrMap.end())
        return LAYER_ERROR;
    else
        return it->second;
}


Direction reverseDirection(Direction input) {
    return Direction(-1 * input);
}


// Generating points on a 3-D line
// using Bresenham's Algorithm
void getLine3D(const Coordinate& start, const Coordinate end, std::vector<Coordinate>& line) {
    line.emplace_back(start);
    int x1 = start.x, y1 = start.y, z1 = start.z;
    int x2 = end.x, y2 = end.y, z2 = end.z;

    int dx, dy, dz;
    int sx, sy, sz;

    if (x2 > x1) {
        dx = x2 - x1;
        sx = 1;
    } else {
        dx = x1 - x2;
        sx = -1;
    }

    if (y2 > y1) {
        dy = y2 - y1;
        sy = 1;
    } else {
        dy = y1 - y2;
        sy = -1;
    }

    if (z2 > z1) {
        dz = z2 - z1;
        sz = 1;
    } else {
        dz = z1 - z2;
        sz = -1;
    }

	// Driving axis is X-axis"
	if (dx >= dy && dx >= dz) {
        printf("x\n");
		int p1 = 2 * dy - dx;
		int p2 = 2 * dz - dx;
		while (x1 != x2) {
			x1 += sx;
			if (p1 >= 0) {
				y1 += sy;
				p1 -= 2 * dx;
            }
			if (p2 >= 0) {
				z1 += sz;
				p2 -= 2 * dx;
            }
			p1 += 2 * dy;
			p2 += 2 * dz;
            line.emplace_back(x1, y1, z1);
        }
    }

	// Driving axis is Y-axis"
	else if (dy >= dx && dy >= dz) {
        printf("y\n");
		int p1 = 2 * dx - dy;
		int p2 = 2 * dz - dy;
		while (y1 != y2) {
			y1 += sy;
			if (p1 >= 0) {
				x1 += sx;
				p1 -= 2 * dy;
            }
			if (p2 >= 0) {
				z1 += sz;
				p2 -= 2 * dy;
            }
			p1 += 2 * dx;
			p2 += 2 * dz;
            line.emplace_back(x1, y1, z1);
        }
    }

	// Driving axis is Z-axis"
    else {
        printf("z\n");
		int p1 = 2 * dy - dz;
		int p2 = 2 * dx - dz;
		while (z1 != z2) {
			z1 += sz;
			if (p1 >= 0) {
				y1 += sy;
				p1 -= 2 * dz;
            }
			if (p2 >= 0) {
				x1 += sz;
				p2 -= 2 * dz;
            }
			p1 += 2 * dy;
			p2 += 2 * dx;
            line.emplace_back(x1, y1, z1);
        }
    }
}


} // namespace util

