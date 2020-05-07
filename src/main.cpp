#include "driver/cube.h"
#include "driver/cube_extend.h"
#include "utility/image_lib.h"
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>
#include <wiringPi.h>

/**********************************************
 *
 *   Effects
 *
**********************************************/
#include "effect/layer_scan.h"
#include "effect/random_light.h"
#include "effect/layer_scan.h"
#include "effect/drop_line.h"
#include "effect/drop_point.h"
#include "effect/random_drop_point.h"
#include "effect/drop_text_point.h"
#include "effect/text_scan.h"
#include "effect/cube_size.h"

LedCube cube;

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


int main() {
//    sleepMs(3000);
    if (wiringPiSetupGpio() == -1) {
        printf("Wiringpi setup failed\n");
        return 1;
    }

    // must setup after wiringPiSetupGpio() !
    cube.setup();

//    pinMode(18, OUTPUT);
//
//
//    int count = 1000;
//
//    int drive = 0;
//
//    auto start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < count; ++i) {
//        digitalWrite(18, drive);
//        drive = 1 - drive;
//    }
//
//    digitalWrite(18, LOW);
//
//    auto end = std::chrono::high_resolution_clock::now();
//    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
//    std::cout << dur.count() / double(count) << std::endl;
//
//    return 0;

    /***************************************************
     *
     *           1.  Scan a whole layer
     *
    ***************************************************/
    if (0)
    {
        LayerScanEffect layerScan;
        layerScan.setImagesCode({ Image_Fill });  // light a whole layer
        layerScan.setDirectionsAngles(
             { X_ASCEND,  Z_ASCEND,  Y_ASCEND,  X_DESCEND, Y_DESCEND, Z_DESCEND },
             { X_ASCEND,  Z_ASCEND,  Y_ASCEND,  X_DESCEND, Y_DESCEND, Z_DESCEND },
             { ANGLE_0,   ANGLE_0,   ANGLE_0,   ANGLE_0,   ANGLE_0,   ANGLE_0  }
            );

        // 1.1 slow
        layerScan.setIntervals(100, 50);
        layerScan.showOnce();

        // 1.2 fast
        layerScan.setIntervals(70, 50);
        layerScan.showOnce();
    }

    //return 0;


    /***************************************************
     *
     *           2.  Random light
     *
    ***************************************************/
    if (1)
    {
        RandomLightEffect randomLight;
        randomLight.setInterval(50);
        randomLight.setCount(400);

        randomLight.setStates({ LED_ON, LED_OFF });
        randomLight.showOnce();
    }

    return 0;


    /***************************************************
     *
     *           3.  Drop a line
     *
    ***************************************************/
    if (0)
    {
        DropLineEffect dropLine;
        dropLine.setDirections(
            { X_ASCEND,   X_DESCEND,  X_ASCEND,   X_DESCEND,
              Y_DESCEND,  Y_ASCEND,   Y_DESCEND,  Y_ASCEND,
              Z_ASCEND,   Z_DESCEND,  Z_ASCEND,   Z_DESCEND,
            },
            {
              PARALLEL_Y, PARALLEL_Y, PARALLEL_Z, PARALLEL_Z,
              PARALLEL_X, PARALLEL_X, PARALLEL_Z, PARALLEL_Z,
              PARALLEL_X, PARALLEL_X, PARALLEL_Y, PARALLEL_Y
            }
        );

        dropLine.setIntervals(30, 0);
        dropLine.showOnce();
    }

    //return 0;


    /***************************************************
     *
     *           4.  Drop a point in row
     *
    ***************************************************/
    if (0)
    {
        DropPointEffect dropPoint;
        dropPoint.setDirections(
            { X_ASCEND,   X_DESCEND,  X_ASCEND,   X_DESCEND,
              Y_DESCEND,  Y_ASCEND,   Y_DESCEND,  Y_ASCEND,
              Z_ASCEND,   Z_DESCEND,  Z_ASCEND,   Z_DESCEND,
            },
            {
              PARALLEL_Y, PARALLEL_Y, PARALLEL_Z, PARALLEL_Z,
              PARALLEL_X, PARALLEL_X, PARALLEL_Z, PARALLEL_Z,
              PARALLEL_X, PARALLEL_X, PARALLEL_Y, PARALLEL_Y
            }
        );
        dropPoint.setIntervals(10, 0);
        dropPoint.showOnce();
    }

    //return 0;


    /***************************************************
     *
     *           5.  random drop a point 
     *
    ***************************************************/
    if (0)
    {
        RandomDropPointEffect randomDropPoint;
        randomDropPoint.setDirections({
            X_ASCEND,  X_DESCEND, Y_DESCEND,
            Y_ASCEND,  Z_ASCEND,  Z_DESCEND});
        randomDropPoint.setIntervals(10, 0);
        randomDropPoint.showOnce();
    }

    //return 0;


    /***************************************************
     *
     *           6.  text scan
     *
    ***************************************************/
    if (0)
    {
        TextScanEffect textScan;
        textScan.setText("HAPPY BIRTHDAY TO ME");
        textScan.setDirectionsAngles(
             { X_ASCEND,  Z_ASCEND,  Y_DESCEND },
             { X_ASCEND,  Z_ASCEND,  Y_DESCEND },
             { ANGLE_0,   ANGLE_0,   ANGLE_0   }
            );

        textScan.setIntervals(80, 50);
        textScan.showOnce();
    }

    //return 0;


    /***************************************************
     *
     *           7.  cube size
     *
    ***************************************************/
    if (1) {
        CubeSizeEffect cubeSize;
        cubeSize.setDirections(
            {
                X_ASCEND,  X_ASCEND,  X_ASCEND,  X_ASCEND,
                X_ASCEND,  X_ASCEND,  X_ASCEND,  X_ASCEND
            //    X_DESCEND, X_DESCEND, X_DESCEND, X_DESCEND,
             //   X_DESCEND, X_DESCEND, X_DESCEND, X_DESCEND
            },
            {
                Y_ASCEND,  Y_ASCEND,  Y_ASCEND,  Y_ASCEND,
                Y_DESCEND, Y_DESCEND, Y_DESCEND, Y_DESCEND
              //  Y_ASCEND,  Y_ASCEND,  Y_ASCEND,  Y_ASCEND,
               // Y_DESCEND, Y_DESCEND, Y_DESCEND, Y_DESCEND
            },
            {
                Z_ASCEND,  Z_ASCEND,  Z_DESCEND, Z_DESCEND,
                Z_ASCEND,  Z_ASCEND,  Z_DESCEND, Z_DESCEND
            //    Z_ASCEND,  Z_ASCEND,  Z_DESCEND, Z_DESCEND,
             //   Z_ASCEND,  Z_ASCEND,  Z_DESCEND, Z_DESCEND
            }
        );
        cubeSize.setChangesType({
                SmallToBig, BigToSmall, SmallToBig, BigToSmall,
                SmallToBig, BigToSmall, SmallToBig, BigToSmall
        //        SmallToBig, BigToSmall, SmallToBig, BigToSmall,
         //       SmallToBig, BigToSmall, SmallToBig, BigToSmall,
            });
        cubeSize.setIntervals(80, 0);
        cubeSize.showOnce();
    }

    return 0;


    /***************************************************
     *
     *           
     *
    ***************************************************/
    if (1) {

    }

    return 0;


    /***************************************************
     *
     *           
     *
    ***************************************************/
    if (1) {

    }

    return 0;


    /***************************************************
     *
     *           
     *
    ***************************************************/
    if (1) {

    }

    return 0;

}

