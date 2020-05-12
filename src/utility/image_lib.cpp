#include "./image_lib.h"
#include "../utility/utils.h"

std::map<int, std::array<std::array<char, 8>, 8>> ImageLib::table =
{
    { '0', util::toBinary({ 0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C }) },
    { '1', util::toBinary({ 0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C }) },
    { '2', util::toBinary({ 0x1C, 0x22, 0x02, 0x02, 0x1C, 0x20, 0x20, 0x3E }) },
    { '3', util::toBinary({ 0x1C, 0x22, 0x02, 0x1C, 0x02, 0x02, 0x22, 0x1C }) },
    { '4', util::toBinary({ 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08, 0x08 }) },
    { '5', util::toBinary({ 0x3E, 0x20, 0x20, 0x3E, 0x02, 0x02, 0x22, 0x1C }) },
    { '6', util::toBinary({ 0x1C, 0x22, 0x20, 0x3C, 0x22, 0x22, 0x22, 0x1C }) },
    { '7', util::toBinary({ 0x3E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10, 0x10 }) },
    { '8', util::toBinary({ 0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x22, 0x1C }) },
    { '9', util::toBinary({ 0x1C, 0x22, 0x22, 0x22, 0x1E, 0x02, 0x22, 0x1C }) },

    { 'A', util::toBinary({ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x3E, 0x22, 0x22 }) },
    { 'B', util::toBinary({ 0x00, 0x3C, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x3C }) },
    { 'C', util::toBinary({ 0x00, 0x1C, 0x22, 0x20, 0x20, 0x20, 0x22, 0x1C }) },
    { 'D', util::toBinary({ 0x00, 0x3C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x3C }) },
    { 'E', util::toBinary({ 0x00, 0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x3E }) },
    { 'F', util::toBinary({ 0x00, 0x3E, 0x20, 0x20, 0x3E, 0x20, 0x20, 0x20 }) },
    { 'G', util::toBinary({ 0x00, 0x1C, 0x22, 0x20, 0x3E, 0x22, 0x22, 0x1C }) },
    { 'H', util::toBinary({ 0x00, 0x22, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22 }) },
    { 'I', util::toBinary({ 0x00, 0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C }) },
    { 'J', util::toBinary({ 0x00, 0x3E, 0x08, 0x08, 0x08, 0x08, 0x28, 0x18 }) },
    { 'K', util::toBinary({ 0x00, 0x20, 0x2C, 0x30, 0x20, 0x30, 0x2C, 0x20 }) },
    { 'L', util::toBinary({ 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E }) },
    { 'M', util::toBinary({ 0x00, 0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x42 }) },
    { 'n', util::toBinary({ 0x00, 0x00, 0x2C, 0x32, 0x22, 0x22, 0x22, 0x22 }) },
    { 'O', util::toBinary({ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C }) },
    { 'P', util::toBinary({ 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x20, 0x20, 0x20 }) },
    { 'Q', util::toBinary({ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x2A, 0x26, 0x1F }) },
    { 'R', util::toBinary({ 0x00, 0x38, 0x24, 0x24, 0x38, 0x30, 0x28, 0x24 }) },
    { 'S', util::toBinary({ 0x00, 0x1C, 0x22, 0x20, 0x1C, 0x02, 0x22, 0x1C }) },
    { 'T', util::toBinary({ 0x00, 0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 }) },
    { 'U', util::toBinary({ 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C }) },
    { 'V', util::toBinary({ 0x00, 0x22, 0x22, 0x22, 0x14, 0x14, 0x08, 0x00 }) },
    { 'W', util::toBinary({ 0x00, 0x41, 0x41, 0x49, 0x55, 0x55, 0x63, 0x41 }) },
    { 'X', util::toBinary({ 0x00, 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42 }) },
    { 'Y', util::toBinary({ 0x00, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08 }) },
    { 'Z', util::toBinary({ 0x00, 0x3E, 0x02, 0x04, 0x08, 0x10, 0x20, 0x3E }) },

    { ' ', util::toBinary({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }) },
    { '!', util::toBinary({ 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08 }) },

    { Image_Fill , util::toBinary({ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }) },

    { Image_Square_Edge_1,  util::toBinary({ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 }) },
    { Image_Square_Edge_2,  util::toBinary({ 0x00, 0x00, 0x3C, 0x24, 0x24, 0x3C, 0x00, 0x00 }) }, 
    { Image_Square_Edge_3,  util::toBinary({ 0x00, 0x7E, 0x22, 0x22, 0x22, 0x22, 0x7E, 0x00 }) },
    { Image_Square_Edge_4,  util::toBinary({ 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF }) },

    { Image_Square_Solid_1, util::toBinary({ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 }) },
    { Image_Square_Solid_2, util::toBinary({ 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00 }) },
    { Image_Square_Solid_3, util::toBinary({ 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00 }) },
    { Image_Square_Solid_4, util::toBinary({ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }) },

    { Image_Circle_Edge_1,  util::toBinary({ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 }) },
    { Image_Circle_Edge_2,  util::toBinary({ 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00 }) },
    { Image_Circle_Edge_3,  util::toBinary({ 0x00, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00 }) }, 
    { Image_Circle_Edge_4,  util::toBinary({ 0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c }) }, 
    { Image_Circle_Edge_5,  util::toBinary({ 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81 }) },

    { Image_Circle_Solid_1, util::toBinary({ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 }) },
    { Image_Circle_Solid_2, util::toBinary({ 0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00 }) },
    { Image_Circle_Solid_3, util::toBinary({ 0x00, 0x18, 0x3C, 0x7E, 0x7E, 0x3C, 0x18, 0x00 }) },
    { Image_Circle_Solid_4, util::toBinary({ 0x3c, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C }) },
    { Image_Circle_Solid_5, util::toBinary({ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }) },
};

std::map<std::string, int> ImageLib::keyTable =
{
    { "NUM_0", Num_0 },
    { "NUM_1", Num_1 },
    { "NUM_2", Num_2 },
    { "NUM_3", Num_3 },
    { "NUM_4", Num_4 },
    { "NUM_5", Num_5 },
    { "NUM_6", Num_6 },
    { "NUM_7", Num_7 },
    { "NUM_8", Num_8 },
    { "NUM_9", Num_9 },
    { "0", Num_0 },
    { "1", Num_1 },
    { "2", Num_2 },
    { "3", Num_3 },
    { "4", Num_4 },
    { "5", Num_5 },
    { "6", Num_6 },
    { "7", Num_7 },
    { "8", Num_8 },
    { "9", Num_9 },
    { "LETTER_A", Letter_A },
    { "LETTER_B", Letter_B },
    { "LETTER_C", Letter_C },
    { "LETTER_D", Letter_D },
    { "LETTER_E", Letter_E },
    { "LETTER_F", Letter_F },
    { "LETTER_G", Letter_G },
    { "LETTER_H", Letter_H },
    { "LETTER_I", Letter_I },
    { "LETTER_J", Letter_J },
    { "LETTER_K", Letter_K },
    { "LETTER_L", Letter_L },
    { "LETTER_M", Letter_M },
    { "LETTER_n", Letter_n },
    { "LETTER_O", Letter_O },
    { "LETTER_P", Letter_P },
    { "LETTER_Q", Letter_Q },
    { "LETTER_R", Letter_R },
    { "LETTER_S", Letter_S },
    { "LETTER_T", Letter_T },
    { "LETTER_U", Letter_U },
    { "LETTER_V", Letter_V },
    { "LETTER_W", Letter_W },
    { "LETTER_X", Letter_X },
    { "LETTER_Y", Letter_Y },
    { "LETTER_Z", Letter_Z },
    { "A", Letter_A },
    { "B", Letter_B },
    { "C", Letter_C },
    { "D", Letter_D },
    { "E", Letter_E },
    { "F", Letter_F },
    { "G", Letter_G },
    { "H", Letter_H },
    { "I", Letter_I },
    { "J", Letter_J },
    { "K", Letter_K },
    { "L", Letter_L },
    { "M", Letter_M },
    { "n", Letter_n },
    { "O", Letter_O },
    { "P", Letter_P },
    { "Q", Letter_Q },
    { "R", Letter_R },
    { "S", Letter_S },
    { "T", Letter_T },
    { "U", Letter_U },
    { "V", Letter_V },
    { "W", Letter_W },
    { "X", Letter_X },
    { "Y", Letter_Y },
    { "Z", Letter_Z },
    { "IMAGE_SPACE", Image_Space },
    { "IMAGE_FILL",  Image_Fill },
    { "IMAGE_SQUARE_EDGE_1",  Image_Square_Edge_1 },
    { "IMAGE_SQUARE_EDGE_2",  Image_Square_Edge_2 },
    { "IMAGE_SQUARE_EDGE_3",  Image_Square_Edge_3 },
    { "IMAGE_SQUARE_EDGE_4",  Image_Square_Edge_4 },
    { "IMAGE_SQUARE_SOLID_1", Image_Square_Solid_1 },
    { "IMAGE_SQUARE_SOLID_2", Image_Square_Solid_2 },
    { "IMAGE_SQUARE_SOLID_3", Image_Square_Solid_3 },
    { "IMAGE_SQUARE_SOLID_4", Image_Square_Solid_4 },
    { "IMAGE_CIRCLE_EDGE_1",  Image_Circle_Edge_1 },
    { "IMAGE_CIRCLE_EDGE_2",  Image_Circle_Edge_2 },
    { "IMAGE_CIRCLE_EDGE_3",  Image_Circle_Edge_3 },
    { "IMAGE_CIRCLE_EDGE_4",  Image_Circle_Edge_4 },
    { "IMAGE_CIRCLE_EDGE_5",  Image_Circle_Edge_5 },
    { "IMAGE_CIRCLE_SOLID_1", Image_Circle_Solid_1 },
    { "IMAGE_CIRCLE_SOLID_2", Image_Circle_Solid_2 },
    { "IMAGE_CIRCLE_SOLID_3", Image_Circle_Solid_3 },
    { "IMAGE_CIRCLE_SOLID_4", Image_Circle_Solid_4 },
    { "IMAGE_CIRCLE_SOLID_5", Image_Circle_Solid_5 },
};


bool ImageLib::exist(int key) {
    auto findIter = ImageLib::table.find(key);
    return findIter != ImageLib::table.end();
}

const std::array<std::array<char, 8>, 8>& ImageLib::get(int key) {
    auto findIter = ImageLib::table.find(key);
    if (findIter == ImageLib::table.end()) {
        return ImageLib::table[' '];
    }
    else
        return findIter->second;
}

bool ImageLib::exist(const std::string& keyStr) {
    std::string keyStrTmp = keyStr;
    util::toUpperCase(keyStrTmp);
    auto findIter = ImageLib::keyTable.find(keyStrTmp);
    if (findIter == ImageLib::keyTable.end())
        return false;
    else
        return exist(findIter->second);
}

int ImageLib::getKey(const std::string& keyStr) {
    std::string keyStrTmp = keyStr;
    util::toUpperCase(keyStrTmp);
    auto findIter = ImageLib::keyTable.find(keyStrTmp);
    if (findIter == ImageLib::keyTable.end())
        return -1;
    else
        return findIter->second;
}

void ImageLib::validate(std::string& str) {
    for (auto iter = str.begin(); iter != str.end(); ) {
        char ch = *iter;
        if (ImageLib::exist(ch))
            ++iter;
        else if (ch >= 'a' && ch <= 'z') {
            *iter = ch - 32;
            ++iter;
        }
        else
            iter = str.erase(iter);
    }
}

