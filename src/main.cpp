#include "driver/cube.h"
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
#include "effect/drop_text.h"
#include "effect/drop_text_point.h"

LedCube cube;

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("Wiringpi setup failed\n");
        return 1;
    }

    if (!cube.setup()) {
        printf("Cube setup failed!\n");
        return 1;
    }

    int skip = 0;

    // 1 Layer scan (slow)
    skip = 0;
    if (!skip)
    {
        LayerScanEffect layerScan;
        //layerScan.setDirections({X_ASCEND, Y_ASCEND, Z_ASCEND, X_DESCEND, Y_DESCEND, Z_DESCEND});
        // equal to:
        layerScan.setDefaultDirections();

        // 1.1 slow
        layerScan.setInterval(160, 1);
        layerScan.showOnce();

        // 1.2 fast
        layerScan.setInterval(80, 1);
        layerScan.showOnce();
    }

    // 2. random light on
    skip = 0;
    if (!skip)
    {
        RandomLightEffect randomLight;
        randomLight.setInterval(50);
        randomLight.setCount(300);
        randomLight.showOnce();
    }

    // 3. drop a line
    skip = 0;
    if (!skip)
    {
        DropLineEffect dropLine;
        dropLine.setInterval(30);
        dropLine.setDefaultDirections();
        dropLine.showOnce();
    }

    // 4. drop a point 
    skip = 0;
    if (!skip)
    {
        DropPointEffect dropPoint;
        dropPoint.setInterval(10);
        dropPoint.setDefaultDirections();
        dropPoint.showOnce();
    }

    // 5. random drop a point 
    skip = 0;
    if (!skip)
    {
        RandomDropPointEffect randomDropPoint;
        randomDropPoint.setInterval(10);
        randomDropPoint.setDefaultDirections();
        randomDropPoint.showOnce();
    }

    // 6. drop text point
    skip = 0;
    if (!skip)
    {
        DropTextPointEffect dropTextPoint;
        dropTextPoint.setDirectionsAngles(
             { X_ASCEND,  X_DESCEND, Y_ASCEND,  Y_DESCEND, Z_ASCEND,  Z_DESCEND },
             { X_DESCEND, X_ASCEND,  Y_DESCEND, Y_ASCEND,  Z_DESCEND, Z_ASCEND  },
             { ANGLE_0,   ANGLE_0,   ANGLE_0,   ANGLE_0,   ANGLE_0,   ANGLE_0   }
            );
        dropTextPoint.setInterval(15, 200);
        dropTextPoint.setString("Misaka");
        dropTextPoint.showOnce();
    }

    // 7. drop text
    skip = 0;
    if (!skip)
    {
        DropTextEffect dropText;
        dropText.setDirectionsAngles(
             { X_ASCEND,  Y_DESCEND, Z_ASCEND },
             { X_ASCEND,  Y_DESCEND, Z_ASCEND },
             { ANGLE_0,   ANGLE_0,   ANGLE_0  }
            );
        dropText.setInterval(100, 100);
        dropText.setString("Misaka");

        dropText.setTogetherLayers(1);
        dropText.showOnce();

        dropText.setTogetherLayers(2);
        dropText.showOnce();
    }

    // 8. Happy birthday to misaka mikoto
    skip = 1;
    if (!skip)
    {
        cube.showStringInLayerX("0502", 600, 7, X_ASCEND, ANGLE_0);
        Call(cube.clear());
        sleepMs(1000);
        cube.showStringInLayerX("HAPPY BIRTHDAY TO MISAKA MIKOTO", 500, 7, X_ASCEND, ANGLE_0);
        sleepMs(1000);

        std::string str = "0502 HAPPY BIRTHDAY TO MISAKA MIKOTO";
        DropTextPointEffect dropTextPoint;
        dropTextPoint.setInterval(12, 200);
        dropTextPoint.setString(str);

        DropTextEffect dropText;
        dropText.setInterval(150, 50);
        dropText.setString(str);

        // Layer X
        dropTextPoint.setDirectionsAngles({ X_ASCEND }, { X_ASCEND }, { ANGLE_0 });
        dropTextPoint.showOnce();
        sleepMs(1000);

        dropText.setDirectionsAngles( { X_ASCEND }, { X_ASCEND }, { ANGLE_0 });
        dropText.setTogetherLayers(1);
        dropText.showOnce();
        sleepMs(1000);

        dropText.setDirectionsAngles({ X_ASCEND }, { X_ASCEND }, { ANGLE_0 });
        dropText.setTogetherLayers(2);
        dropText.showOnce();
        sleepMs(1000);

        return 0;

        // Layer Y
        dropTextPoint.setDirectionsAngles({ Y_DESCEND }, { Y_DESCEND }, { ANGLE_0 });
        dropTextPoint.showOnce();

        dropText.setDirectionsAngles( { Y_DESCEND }, { Y_DESCEND }, { ANGLE_0 });
        dropText.setTogetherLayers(1);
        dropText.showOnce();

        dropText.setDirectionsAngles({ Y_DESCEND }, { Y_DESCEND }, { ANGLE_0 });
        dropText.setTogetherLayers(2);
        dropText.showOnce();

        // Layer Z
        dropTextPoint.setDirectionsAngles({ Z_ASCEND }, { Z_ASCEND }, { ANGLE_0 });
        dropTextPoint.showOnce();

        dropText.setDirectionsAngles( { Z_ASCEND }, { Z_ASCEND }, { ANGLE_0 });
        dropText.setTogetherLayers(1);
        dropText.showOnce();

        dropText.setDirectionsAngles({ Z_ASCEND }, { Z_ASCEND }, { ANGLE_0 });
        dropText.setTogetherLayers(2);
        dropText.showOnce();
    }

    return 0;
}

