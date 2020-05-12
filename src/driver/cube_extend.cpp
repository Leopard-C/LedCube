#include "cube_extend.h"
#include "../utility/ExpressionEvaluator.h"
#include "../utility/image_lib.h"

extern LedCube cube;

namespace ext {


static void replaceAll(std::string& str, const std::string& src, const std::string& des) {
    std::string::size_type pos = 0;
    std::string::size_type srcLen = src.length();
    std::string::size_type desLen = des.length();
    pos = str.find(src, pos);
    while (pos != std::string::npos) {
        str.replace(pos, srcLen, des);
        pos = src.find(src, pos + desLen);
    }
}

static void getValueZ(std::string func, int x, int y, char zArr[]) {

}


void getFrameOfFunction(std::string func, char leds[][8][8]) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            std::string expression = func;
            replaceAll(expression, "x", std::to_string(x));
            replaceAll(expression, "y", std::to_string(y));
            replaceAll(expression, "=", "-(");
            expression += ")";

            std::cout << expression << std::endl;

            ExpressionEvaluator expEv;
            double val;

            for (int z = 0; z < 8; ++z) {
                std::string expTmp = expression;
                replaceAll(expTmp, "z", std::to_string(z));
                val = expEv.eval(expTmp);
                if (val > -0.5 && val < 0.5)
                    cube(x, y, z) = LED_ON;
                    //leds[z][x][y] = LED_ON;
                else
                    cube(x, y, z) = LED_OFF;
                    //leds[z][x][y] = LED_OFF;
            }
        }
    }

    cube.update();
}


} // namespace ext
