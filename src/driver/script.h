#pragma once
#include <string>
#include <array>
#include <set>
#include "../driver/cube_extend.h"


class Script {
public:
    bool run(const char* filename);

    bool isCmd(const std::string& str);

private:
    bool parseCmd(const std::string& cmd, std::stringstream& ssLine);
    bool cmdLight(LedState state, std::stringstream& ssLine);
    bool cmdSleepMs(std::stringstream& ssLine);
    bool cmdSquare(std::stringstream& ssLine);
    bool cmdCube(std::stringstream& ssLine);

    void getRange(const std::string& str, int& start, int& end);
    void getArray(const std::string& str, char state, std::array<char, 8>& states);
    bool getArray(const std::string& str, std::array<char, 8>& states);

private:
    static std::set<std::string> cmds; 
};

