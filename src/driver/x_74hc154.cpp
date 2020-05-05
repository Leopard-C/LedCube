#include "./x_74hc154.h"
#include <iostream>
#include <wiringPi.h>

void X74hc154::setup(int a, int b, int c, int d, int g) {
    pinA = a;
    pinB = b;
    pinC = c;
    pinD = d;
    pinG = g;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);

    pinMode(pinG, OUTPUT);

    enable(false);
}

void X74hc154::enable(bool isEnable) {
    digitalWrite(pinG, isEnable ? LOW : HIGH);
}

void X74hc154::setOutput(char code) {
    // digit to binary
    int input[4] = { 0 };
    int j = 0;
    char i = code;

    while (i) {
        input[j] = i % 2;
        i /= 2;
        j++;
    }

    //printf("code: %2d ", code);
    //for (int i = 3; i > -1; --i)
    //    printf("%d", input[i]);
    //printf("\n");

    digitalWrite(pinA, input[0]);
    digitalWrite(pinB, input[1]);
    digitalWrite(pinC, input[2]);
    digitalWrite(pinD, input[3]);
}

