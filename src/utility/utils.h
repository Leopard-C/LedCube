#pragma once
#include <vector>
#include <array>

namespace util {

std::vector<int> getRandomArray(int len);

std::array<std::array<unsigned char, 8>, 8> toBinary(std::array<unsigned char, 8> arr);

} // namespace util
