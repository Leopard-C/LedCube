#include "./drop_text_point.h"
#include "../utility/image_lib.h"
#include "../utility/utils.h"


void DropTextPointEffect::setText(const std::string& str) {
    string_ = str;
    ImageLib::validate(string_);
    DropPointEffect::clearImagesCode();
    for (auto ch : string_) {
        DropPointEffect::emplaceImagesCode(ch);
    }
}


bool DropTextPointEffect::readFromFP(FILE* fp) {
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
                    char viewDirection[32] = { 0 };
                    char scanDirection[12] = { 0 };
                    char parallel[12] = { 0 };
                    char rotate[12] = { 0 };
                    char is_S_Shape[12] = { 0 };
                    char isSShape = false;
                    int together, interval1, interval2;
                    fscanf(fp, "%s %s %s %s %d %d %d", viewDirection, scanDirection,
                            parallel, rotate, &together, &interval1, &interval2);
                    if (strcmp(is_S_Shape, "S_SHAPE") == 0)
                        isSShape = true;
                    events_.emplace_back(
                            util::getDirection(viewDirection), util::getDirection(scanDirection),
                            util::getDirection(parallel), util::getAngle(rotate),
                            isSShape, together, interval1, interval2);
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


