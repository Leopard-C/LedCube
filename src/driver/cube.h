#pragma once

#include "./x_74hc154.h"
#include "../utility/directions.h"
#include <mutex>
#include <array>
#include <iostream>

#define LED_ON  1
#define LED_OFF 0

using LedState = char;

#define Call(x) (x); LedCube::update();

struct Coordinate {
    Coordinate(int x = 0, int y = 0, int z = 0) :
        x(x), y(y), z(z) {}
    int x;
    int y;
    int z;
};

inline std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
    os << "(" << coord.x << ", " << coord.y << ", " << coord.y << ")";
    return os;
}


class LedCube {
public:
    LedCube() {}
    ~LedCube();

    /*************************
     * initialize
    *************************/
    void setup();

    /*********************************************
     * copy and apply the LEDs state buffer
     * refresh the cube
    *********************************************/
    static void update();

    /****************************
     *     Light off All LEDs
    ****************************/
    static void clear();


    /****************************
     *     Led in (x, y, z)
    ****************************/
    LedState& operator()(int x, int y, int z) { return ledsBuff[z][x][y]; }


    /***************************
     *    light a layer
    ***************************/
    void lightLayerX(int x, LedState state);
    void lightLayerY(int y, LedState state);
    void lightLayerZ(int z, LedState state);


    /***************************
     *    light a row
    ***************************/
    void lightRowXY(int x, int y, LedState state);
    void lightRowYZ(int y, int z, LedState state);
    void lightRowXZ(int x, int z, LedState state);


    /********************************
     *    Show Image in a layer
    ********************************/
    using Array2D_8_8 = std::array<std::array<unsigned char, 8>, 8>;
    void getImageInLayerZ(Array2D_8_8& image, unsigned char ch, Direction direction = Z_ASCEND, Angle rotate = ANGLE_0);
    void getImageInLayerY(Array2D_8_8& image, unsigned char ch, Direction direction = Y_ASCEND, Angle rotate = ANGLE_0);
    void getImageInLayerX(Array2D_8_8& image, unsigned char ch, Direction direction = X_ASCEND, Angle rotate = ANGLE_0);

    void setImageInLayerZ(unsigned char ch, int z, Direction direction = Z_ASCEND, Angle rotate = ANGLE_0);
    void setImageInLayerY(unsigned char ch, int y, Direction direction = Y_ASCEND, Angle rotate = ANGLE_0);
    void setImageInLayerX(unsigned char ch, int x, Direction direction = X_ASCEND, Angle rotate = ANGLE_0);

    void setImageInLayerZ(int z, const Array2D_8_8& image);
    void setImageInLayerY(int y, const Array2D_8_8& image);
    void setImageInLayerX(int x, const Array2D_8_8& image);

    void showStringInLayerZ(std::string str, int interval, int z, Direction direction = Z_ASCEND, Angle rotate = ANGLE_0);
    void showStringInLayerY(std::string str, int interval, int y, Direction direction = Y_ASCEND, Angle rotate = ANGLE_0);
    void showStringInLayerX(std::string str, int interval, int x, Direction direction = X_ASCEND, Angle rotate = ANGLE_0);

private:
    static void backgroundThread();
    static void reset();

private:
    static int vcc[8];
    static X74hc154 x74hc154[4];

    static LedState leds[8][8][8];  // Z X Y
    static LedState ledsBuff[8][8][8];  // Z X Y

    static bool isRunning;
    static bool isBackgroundThreadQuit;
    static std::mutex mutex_;
};

