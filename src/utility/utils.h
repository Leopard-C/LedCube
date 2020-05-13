#pragma once
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include "./enum.h"
#include "./coordinate.h"


namespace util
{
    void trim(std::string& str);
    bool isNum(const std::string& str);
    bool isInt(const std::string& str);

    template <typename output_type, typename input_type>
    output_type convert(const input_type& input) {
        std::stringstream ss;
        ss << input;
        output_type result;
        ss >> result;
        return result;
    }

    std::vector<int> getRandomArray(int len);
    std::vector<int> getRandomArray(int count, int all);


    // { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
    //      ====>
    // {
    //   { 1, 1, 1, 1, 1, 1, 1, 1 }
    //   { 1, 1, 1, 1, 1, 1, 1, 1 }
    //   { 1, 1, 1, 1, 1, 1, 1, 1 }
    //   ...
    // }
    std::array<std::array<char, 8>, 8> toBinary(const std::array<unsigned char, 8>& arr);


    // Get the column of an image
    std::array<char, 8> getCol(const std::array<std::array<char, 8>, 8>& image, int col, bool reverse = false);
    //std::array<char, 8>& getRow(const std::array<std::array<char, 8>, 8>& image, int row, bool reverse = false);
    

    void toUpperCase(char* str, int len);
    void toUpperCase(std::string& str);

    
    // Get enum value by it's string(literal)
    Direction getDirection(std::string dirStr);
    Angle getAngle(std::string angleStr);
    ChangeType getChangeType(std::string changeTypeStr);
    FillType getFillType(std::string fillType);
    ShapeType getShape(std::string shape);
    Layer getLayer(std::string layer);


    // Get reversed direction
    //   X_ASCEND  ==> X_DESCEND
    //   Y_ASCEND  ==> Y_DESCEND
    //   ...
    Direction reverseDirection(Direction input);


    // Generating points on a 3-D line
    // using Bresenham's Algorithm
    void getLine3D(const Coordinate& start, const Coordinate end, std::vector<Coordinate>& line);

} // namespace util

