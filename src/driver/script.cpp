#include "./script.h"
#include "../utility/utils.h"
#include "../utility/image_lib.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <set>

extern LedCube cube;

std::set<std::string> Script::cmds = {
    "lightOn", "lightOff", "sleepMs", "update", "clear",
    "square", "cube"
};

bool Script::isCmd(const std::string& str) {
    return cmds.find(str) != cmds.end();
}


bool Script::run(const char* filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open())
        return false;

    std::cout << filename << std::endl;

    std::string line;
    while (getline(ifs, line)) {
        util::trim(line);
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;
        std::cout << "  " << line << std::endl;
        std::stringstream ssLine(line);
        std::string cmd;
        ssLine >> cmd;
        if (!isCmd(cmd)) {
            ifs.close();
            return false;
        }
        if (!parseCmd(cmd, ssLine)) {
            ifs.close();
            return false;
        }
    }

    return true;
}

bool Script::parseCmd(const std::string& cmd, std::stringstream& ssLine) {
    if (cmd == "update") {
        cube.update();
        return true;
    }
    else if (cmd == "clear") {
        cube.clear();
        return true;
    }
    else if (cmd == "sleepMs") {
        return cmdSleepMs(ssLine);
    }

    else if (cmd == "lightOn") {
        return cmdLight(LED_ON, ssLine);
    }
    else if (cmd == "lightOff") {
        return cmdLight(LED_OFF, ssLine);
    }

    else if (cmd == "cube") {
        return cmdCube(ssLine);
    }
    else if (cmd == "square") {
        return cmdSquare(ssLine);
    }

    return false;
}


bool Script::cmdSleepMs(std::stringstream& ssLine) {
    int ms; 
    if (ssLine >> ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));        
        return true;
    }
    return false;
}


bool Script::cmdLight(LedState state, std::stringstream& ssLine) {
    std::string subCmd;
    ssLine >> subCmd;
    if (subCmd == "x") {
        std::string str;
        ssLine >> str;
        int xStart, xEnd;
        getRange(str, xStart, xEnd);
        std::string imageCodeStr;
        ssLine >> imageCodeStr;
        int imageCode = ImageLib::getKey(imageCodeStr);
        if (imageCode != Image_Fill && imageCode != Image_Space) {
            std::string viewDirection, rotate;
            ssLine >> viewDirection >> rotate;
            for (int x = xStart; x <= xEnd; ++x)
                cube.lightLayerX(x, imageCode,
                        util::getDirection(viewDirection), util::getAngle(rotate));
        }
        else {
            for (int x = xStart; x <= xEnd; ++x)
                cube.lightLayerX(x, imageCode, X_ASCEND, ANGLE_0);
        }
    }
    else if (subCmd == "y") {
        std::string str;
        ssLine >> str;
        int yStart, yEnd;
        getRange(str, yStart, yEnd);
        std::string imageCodeStr;
        ssLine >> imageCodeStr;
        int imageCode = ImageLib::getKey(imageCodeStr);
        if (imageCode != Image_Fill && imageCode != Image_Space) {
            std::string viewDirection, rotate;
            ssLine >> viewDirection >> rotate;
            for (int y = yStart; y <= yEnd; ++y)
                cube.lightLayerY(y, imageCode,
                        util::getDirection(viewDirection), util::getAngle(rotate));
        }
        else {
            for (int y = yStart; y <= yEnd; ++y)
                cube.lightLayerY(y, imageCode, Y_ASCEND, ANGLE_0);
        }
    }
    else if (subCmd == "z") {
        std::string str;
        ssLine >> str;
        int zStart, zEnd;
        getRange(str, zStart, zEnd);
        std::string imageCodeStr;
        ssLine >> imageCodeStr;
        int imageCode = ImageLib::getKey(imageCodeStr);
        if (imageCode != Image_Fill && imageCode != Image_Space) {
            std::string viewDirection, rotate;
            ssLine >> viewDirection >> rotate;
            for (int z = zStart; z <= zEnd; ++z)
                cube.lightLayerZ(z, imageCode,
                        util::getDirection(viewDirection), util::getAngle(rotate));
        }
        else {
            for (int z = zStart; z <= zEnd; ++z)
                cube.lightLayerZ(z, imageCode, Z_ASCEND, ANGLE_0);
        }
    }
    else if (subCmd == "xy") {
        int x, y;
        std::string str;
        ssLine >> x >> y >> str;
        std::array<char, 8> states;
        if (!getArray(str, states)) {
            getArray(str, state, states);
        }
        cube.lightRowXY(x, y, states);
    }
    else if (subCmd == "yz") {
        int y, z;
        std::string str;
        ssLine >> y >> z >> str;
        std::array<char, 8> states;
        if (!getArray(str, states)) {
            getArray(str, state, states);
        }
        cube.lightRowYZ(y, z, states);
    }
    else if (subCmd == "xz") {
        int x, z;
        std::string str;
        ssLine >> x >> z >> str;
        std::array<char, 8> states;
        if (!getArray(str, states)) {
            getArray(str, state, states);
        }
        cube.lightRowXZ(x, z, states);
    }
    else if (subCmd == "xyz") {
        int x, y, z;
        ssLine >> x >> y >> z;
        cube(x, y, z) = state;
    }
    else if (subCmd == "line") {
        int x1, y1, z1, x2, y2, z2;
        ssLine >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        cube.lightLine({x1, y1, z1}, {x2, y2, z2}, state);
    }

    return true;
}


bool Script::cmdSquare(std::stringstream& ssLine) {
    Coordinate coord1, coord2;
    std::string fillType;
    ssLine >> coord1.x >> coord1.y >> coord1.z
        >> coord2.x >> coord2.y >> coord2.z
        >> fillType;
    ext::lightSqure(coord1, coord2, util::getFillType(fillType));
    return true;
}

bool Script::cmdCube(std::stringstream& ssLine) {
    Coordinate coord1, coord2;
    std::string fillType;
    ssLine >> coord1.x >> coord1.y >> coord1.z
        >> coord2.x >> coord2.y >> coord2.z
        >> fillType;
    ext::lightCube(coord1, coord2, util::getFillType(fillType));
    return true;
}

void Script::getRange(const std::string& str, int& start, int& end) {
    auto pos = str.find(":");
    if (pos == std::string::npos) {
        start = end = util::convert<int>(str);
    }
    else {
        start = util::convert<int>(str.substr(0, pos));
        end = util::convert<int>(str.substr(pos + 1));
    }
}

void Script::getArray(const std::string& str, char state, std::array<char, 8>& states) {
    int start, end;
    getRange(str, start, end);
    for (int i = start; i <= end; ++i) {
        states[i] = state;
    }
}

bool Script::getArray(const std::string& str, std::array<char, 8>& states) {
    int len = str.length();
    if (len != 8) {
        return false;
    }
    for (int i = 0; i < 8; ++i) {
        if (str[i] == '1')
            states[i] = LED_ON;
        else
            states[i] = LED_OFF;
    }
    return true;
}


