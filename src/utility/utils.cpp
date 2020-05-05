#include "utils.h"

#include <algorithm>

namespace util {

    
std::vector<int> getRandomArray(int len) {
    std::vector<int> vec;
    vec.reserve(len);
    for (int i = 0; i < len; ++i)
        vec.push_back(i);
    std::random_shuffle(vec.begin(), vec.end());
    return vec;
}

static void toBinary(unsigned char c, std::array<unsigned char, 8>& bin) {
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

// { 0xff, 0x00, 0x01, ... } ==> { 1, 1, 1, ... }
std::array<std::array<unsigned char, 8>, 8> toBinary(std::array<unsigned char, 8> arr) {
    std::array<std::array<unsigned char, 8>, 8> retBin;
    for (int i = 0; i < 8; ++i) {
        toBinary(arr[i], retBin[i]);
    }
    return retBin;
}

} // namespace util
