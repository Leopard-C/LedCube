#pragma once


/***************  ENUM  *********************/
enum LED_State:char {
    LED_ON  = 1,
    LED_OFF = 0
};

enum Direction {
    DIR_ERROR = 0,
    X_ASCEND  = 1,
    X_DESCEND = -1,
    Y_ASCEND  = 2,
    Y_DESCEND = -2,
    Z_ASCEND  = 3,
    Z_DESCEND = -3,

    PARALLEL_X = 10,
    PARALLEL_Y = 11,
    PARALLEL_Z = 12
}; 

enum Angle {
    ANGLE_ERROR = -1,
    ANGLE_0   = 0,
    ANGLE_90  = 90,
    ANGLE_180 = 180,
    ANGLE_270 = 270
};

enum ChangeType {
    CHANGETYPE_ERROR = -1,
    SMALL_TO_BIG = 0,
    BIG_TO_SMALL = 1,
};


enum FillType {
    CUBEFILL_ERROR = -1,
    FILL_EDGE    = 0,
    FILL_SURFACE = 1,
    FILL_SOLID   = 2
};

enum ShapeType {
    SHAPE_ERROR = -1,
    POINT     = 0,   
    LINE      = 1,
    RECTANGLE = 2,
    TRIANGLE  = 3,
    CIRCLE    = 4
};

enum Layer {
    LAYER_ERROR = -1,
    LAYER_X = 0,
    LAYER_Y = 1,
    LAYER_Z = 2,
    LAYER_XY45  = 3,
    LAYER_XY135 = 4
};

