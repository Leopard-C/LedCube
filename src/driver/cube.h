#pragma once

#include "./x_74hc154.h"
#include "../utility/directions.h"
#include <mutex>
#include <array>

#define LED_ON  1
#define LED_OFF 0

#define Call(x) LedCube::lock(); (x); LedCube::unlock();


class LedCube {
public:
    LedCube() {}
    ~LedCube();

    bool setup();

    static void lock();
    static void unlock();

    /****************************
     *     Light off All LEDs
    ****************************/
    void clear();


    /****************************
     *     Led in (x, y, z)
    ****************************/
    int& operator()(int x, int y, int z) { return leds[z][x][y]; }


    /***************************
     *         Layer
    ***************************/
    void lightLayerX(int x, int state);
    void lightLayerY(int y, int state);
    void lightLayerZ(int z, int state);


    /***************************
     *        Row
    ***************************/
    void lightRowXY(int x, int y, int state);
    void lightRowYZ(int y, int z, int state);
    void lightRowXZ(int x, int z, int state);


    /********************************
     *      Show Text or Image
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
    static void lightRowX(int z, int x);
    static void lightOffAll();

private:
    static int vcc[8];
    static X74hc154 x74hc154[4];

    static int leds[8][8][8];  // Z X Y

    static bool isRunning;
    static bool isBackgroundThreadQuit;

    static std::mutex mutex_;
};

