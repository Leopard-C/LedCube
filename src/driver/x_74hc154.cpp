#include "./x_74hc154.h"
#include <iostream>
#include <cstring>
#include <wiringPi.h>

int X74hc154::hex[16][4] =
{
    { 0, 0, 0, 0 },    // 0x00
    { 0, 0, 0, 1 },    // 0x01
    { 0, 0, 1, 0 },    // 0x02
    { 0, 0, 1, 1 },    // 0x03
    { 0, 1, 0, 0 },    // 0x04
    { 0, 1, 0, 1 },    // 0x05
    { 0, 1, 1, 0 },    // 0x06
    { 0, 1, 1, 1 },    // 0x07
    { 1, 0, 0, 0 },    // 0x08
    { 1, 0, 0, 1 },    // 0x09
    { 1, 0, 1, 0 },    // 0x0A
    { 1, 0, 1, 1 },    // 0x0B
    { 1, 1, 0, 0 },    // 0x0C
    { 1, 1, 0, 1 },    // 0x0D
    { 1, 1, 1, 0 },    // 0x0E
    { 1, 1, 1, 1 },    // 0x0F
};


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

    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinG, HIGH);

    last_input = hex[0];

    enable(false);
}

void X74hc154::enable(bool isEnable) {
    digitalWrite(pinG, isEnable ? LOW : HIGH);
}

void X74hc154::setOutput(char code) {
    // digit to binary
    int* input = hex[code];

    if (input[0] != last_input[0]) {
        digitalWrite(pinD, input[0]);
    }
    if (input[1] != last_input[1]) {
        digitalWrite(pinC, input[1]);
    }
    if (input[2] != last_input[2]) {
        digitalWrite(pinB, input[2]);
    }
    if (input[3] != last_input[3]) {
        digitalWrite(pinA, input[3]);
    }

    last_input = input;
}

