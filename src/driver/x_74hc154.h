#pragma once

class X74hc154 {
public:
    void setup(int pinA, int pinB, int pinC, int pinD, int pinG);

    void enable(bool isEnable);
    void setOutput(char code);
    void update();

private:
    int pinA, pinB, pinC, pinD;
    int pinG;
};

