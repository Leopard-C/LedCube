#include "./text_scan.h"
#include "../utility/image_lib.h"
#include "../utility/utils.h"
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


bool TextScanEffect::readFromFP(FILE* fp) {
    while (!feof(fp)) {
        char tag1[32] = { 0 };
        fscanf(fp, "%s", tag1);
        util::toUpperCase(tag1, strlen(tag1));

        if (strcmp(tag1, "<TEXTS>") == 0) {
            while (true) {
                char tag2[32] = { 0 };
                fscanf(fp, "%s", tag2);
                util::toUpperCase(tag2, strlen(tag2));
                if (strcmp(tag2, "<TEXT>") == 0) {
                    char text[256] = { 0 };
                    fgets(text, 256, fp);
                    this->setText(text);
                }
                else if (strcmp(tag2, "<END_TEXTS>") == 0) {
                    break;
                }
                else if (strcmp(tag2, "<END>") == 0) {
                    return true;
                }
            }
        }
        else if (strcmp(tag1, "<EVENTS>") == 0) {
            while (true) {
                char tag2[32] = { 0 };
                fscanf(fp, "%s", tag2);
                util::toUpperCase(tag2, strlen(tag2));
                if (strcmp(tag2, "<EVENT>") == 0) {
                    char viewDirection[12] = { 0 };
                    char scanDirection[12] = { 0 };
                    char rotate[12] = { 0 };
                    int together, interval1, interval2;
                    fscanf(fp, "%s %s %s %d %d %d", viewDirection, scanDirection,
                            rotate, &together, &interval1, &interval2);
                    events_.emplace_back(util::getDirection(viewDirection),
                            util::getDirection(scanDirection),
                            util::getAngle(rotate), together, interval1, interval2);
                }
                else if (strcmp(tag2, "<END_EVENTS>") == 0) {
                    break;
                }
                else if (strcmp(tag2, "<END>") == 0) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else if (strcmp(tag1, "<END>") == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    return true;
}


