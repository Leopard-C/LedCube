#pragma once

#include "./x_74hc154.h"
#include "../utility/enum.h"
#include "../utility/coordinate.h"
#include <mutex>
#include <array>
#include <iostream>

#define Call(x) (x); LedCube::update();

using LedState = char;


/*******************************************************/
/*                                                     */
/*                   class: LedCube                    */
/*                                                     */
/*******************************************************/

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

    /*********************************************
     *  Quit background thread
    *********************************************/
    static void quit();

    /****************************
     *     Light off All LEDs
    ****************************/
    static void clear();


    /****************************
     *     Led in (x, y, z)
    ****************************/
    LedState& operator()(int x, int y, int z)
        { return ledsBuff[z][x][y]; }
    LedState& operator()(const Coordinate& coord)
        { return ledsBuff[coord.z][coord.x][coord.y]; }


    /***************************
     *    light a layer
    ***************************/
    using Array2D_8_8 = std::array<std::array<char, 8>, 8>;
    void lightLayerZ(int z, LedState state);
    void lightLayerY(int y, LedState state);
    void lightLayerX(int x, LedState state);

    void lightLayerZ(int z, const Array2D_8_8& image);
    void lightLayerY(int y, const Array2D_8_8& image);
    void lightLayerX(int x, const Array2D_8_8& image);

    void lightLayerZ(int z, int imageCode, Direction viewDirection, Angle rotate = ANGLE_0);
    void lightLayerY(int y, int imageCode, Direction viewDirection, Angle rotate = ANGLE_0);
    void lightLayerX(int x, int imageCode, Direction viewDirection, Angle rotate = ANGLE_0);


    /***************************
     *    light a row
    ***************************/
    void lightRowXY(int x, int y, LedState state);  // the same state
    void lightRowYZ(int y, int z, LedState state);  
    void lightRowXZ(int x, int z, LedState state);
    void lightRowXY(int x, int y, int zStart, int zEnd, LedState state);  // the same state
    void lightRowYZ(int y, int z, int xStart, int xEnd, LedState state);  
    void lightRowXZ(int x, int z, int yStart, int yEnd, LedState state);
    void lightRowXY(int x, int y, const std::array<LedState, 8>& state); // different state
    void lightRowYZ(int y, int z, const std::array<LedState, 8>& state);
    void lightRowXZ(int x, int z, const std::array<LedState, 8>& state);


    /**************************
     *    light a line
    **************************/
    void lightLine(const Coordinate& start, const Coordinate& end, LedState state);


    /********************************
     *    Get Image in a layer
    ********************************/
    void getImageInLayerZ(Array2D_8_8& image, int imageCode, Direction viewDirection = Z_DESCEND, Angle rotate = ANGLE_0);
    void getImageInLayerY(Array2D_8_8& image, int imageCode, Direction viewDirection = Y_DESCEND, Angle rotate = ANGLE_0);
    void getImageInLayerX(Array2D_8_8& image, int imageCode, Direction viewDirection = X_DESCEND, Angle rotate = ANGLE_0);

    void showStringInLayerZ(std::string str, int interval, int z, Direction viewDirection = Z_DESCEND, Angle rotate = ANGLE_0);
    void showStringInLayerY(std::string str, int interval, int y, Direction viewDirection = Y_DESCEND, Angle rotate = ANGLE_0);
    void showStringInLayerX(std::string str, int interval, int x, Direction viewDirection = X_DESCEND, Angle rotate = ANGLE_0);


    /*********************************
     *   Copy (or move) layer
    *********************************/
    void copyLayerZ(int zFrom, int zTo, bool clearZFrom = false);
    void copyLayerY(int yFrom, int yTo, bool clearYFrom = false);
    void copyLayerX(int xFrom, int xTo, bool clearXFrom = false);


    /*********************************
     *   Light a cube (cuboid)
     *   line(A, B) is diagonal line
    *********************************/
    using Vertex = Coordinate;
    void lightCube(const Vertex& A, const Vertex& B, FillType fill);


    /*********************************
     *   Light a square (rectangle)
     *   line(A, B) is diagonal line
    *********************************/
    void lightSqure(const Vertex& A, const Vertex& B, FillType fill);
    void lightSqureInLayerZ(int z, int minX, int maxX, int minY, int maxY, FillType fill);
    void lightSqureInLayerY(int y, int minX, int maxX, int minZ, int maxZ, FillType fill);
    void lightSqureInLayerX(int x, int minY, int maxY, int minZ, int maxZ, FillType fill);

    /*********************************
     *   Light a circle 
    *********************************/
    void lightCircleInLayerX(int x, int diameter, FillType fill);
    void lightCircleInLayerY(int y, int diameter, FillType fill);
    void lightCircleInLayerZ(int z, int diameter, FillType fill);


    static void setLoopCount(int count) {
        if (count == 0)
            loopCount = 150;
        else if (count < 4)
            loopCount = 4;
        else
            loopCount = count;
    }

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
    static int loopCount;

    static bool setuped;
};

