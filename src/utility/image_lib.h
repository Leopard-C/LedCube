#pragma once
#include <map>
#include <array>


enum {
    Num_0     = '0',    Num_1     = '1',
    Num_2     = '2',    Num_3     = '3',
    Num_4     = '4',    Num_5     = '5',
    Num_6     = '6',    Num_7     = '7',
    Num_8     = '8',    Num_9     = '9',

    Letter_A  = 'A',    Letter_B  = 'B',
    Letter_C  = 'C',    Letter_D  = 'D',
    Letter_E  = 'E',    Letter_F  = 'F',
    Letter_G  = 'G',    Letter_H  = 'H',
    Letter_I  = 'I',    Letter_J  = 'J',
    Letter_K  = 'K',    Letter_L  = 'L',
    Letter_M  = 'M',    Letter_n  = 'n',
    Letter_O  = 'O',    Letter_P  = 'P',
    Letter_Q  = 'Q',    Letter_R  = 'R',
    Letter_S  = 'S',    Letter_T  = 'T',
    Letter_U  = 'U',    Letter_V  = 'V',
    Letter_W  = 'W',    Letter_X  = 'X',
    Letter_Y  = 'Y',    Letter_Z  = 'Z',

    Image_Fill             = 255,
    Image_Space            = ' ',
    Image_ExclamationPoint = '!',

    // Other text or image (not in ASCII table)
    Image_Base            = 256,

    Image_Square_Edge_1   = Image_Base + 1,
    Image_Square_Edge_2   = Image_Base + 2,
    Image_Square_Edge_3   = Image_Base + 3,
    Image_Square_Edge_4   = Image_Base + 4,

    Image_Square_Solid_1  = Image_Base + 5,
    Image_Square_Solid_2  = Image_Base + 6,
    Image_Square_Solid_3  = Image_Base + 7,
    Image_Square_Solid_4  = Image_Base + 8,

    Image_Circle_Edge_1   = Image_Base + 9,
    Image_Circle_Edge_2   = Image_Base + 10,
    Image_Circle_Edge_3   = Image_Base + 11,
    Image_Circle_Edge_4   = Image_Base + 12,
    Image_Circle_Edge_5   = Image_Base + 13,

    Image_Circle_Solid_1  = Image_Base + 14,
    Image_Circle_Solid_2  = Image_Base + 15,
    Image_Circle_Solid_3  = Image_Base + 16,
    Image_Circle_Solid_4  = Image_Base + 17,
    Image_Circle_Solid_5  = Image_Base + 18,

    Image_Like        = Image_Base + 30,
    Image_Coin        = Image_Base + 31,
    Image_Collection  = Image_Base + 32,

};


class ImageLib {
public:
    static const std::array<std::array<char, 8>, 8>& get(int ch);
    static bool exist(int key);
    static bool exist(const std::string& keyStr);
    static int getKey(const std::string& keyStr);
    static void validate(std::string& str);

public:
    static std::map<std::string, int> keyTable;
    static std::map<int, std::array<std::array<char, 8>, 8>> table;
};

