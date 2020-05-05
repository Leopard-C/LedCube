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

    Space = ' ',

    // Other text or image (not in ASCII table)
    BASE           = 256
};

class ImageLib {
public:
    static const std::array<std::array<unsigned char, 8>, 8>& get(int ch);
    static bool exist(int key);
    static void validate(std::string& str);

public:
    static std::map<int, std::array<std::array<unsigned char, 8>, 8>> table;
};



