#include "./text_scan.h"
#include "../utility/image_lib.h"
#include <cstring>

void TextScanEffect::setText(std::string text) {
    ImageLib::validate(text);
    int len = text.length();
    std::vector<int> imagesCode;
    imagesCode.reserve(len);
    for (int i = 0; i < len; ++i) {
        imagesCode.push_back(int(text[i]));
    }
    this->setImagesCode(imagesCode);
}

