#pragma once
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <cstring>
#include "../driver/cube.h"

extern LedCube cube;


class Effect {
public:
    void showMillseconds(int millseconds) {
        while (1) {
            auto start = std::chrono::system_clock::now();
            show();
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            if (duration.count() >= millseconds)
                break;
        }
    }

    void showSeconds(int seconds) {
        while (1) {
            auto start = std::chrono::system_clock::now();
            show();
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            if (duration.count() >= seconds)
                break;
        }
    }

    void showCount(int count) {
        for (int i = 0; i < count; ++i)
            show();
    }

    void showOnce() {
        show();
    }

public:
    virtual void show() = 0;
    virtual bool readFromFP(FILE* fp) { return true; };

    virtual bool readFromFile(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (!fp)
            return false;
        bool ret = readFromFP(fp);
        fclose(fp);
        return ret;
    }

protected:
    void sleepUs(int microS) {
        if (microS > 0)
            std::this_thread::sleep_for(std::chrono::microseconds(microS));
    }

    void sleepMs(int milliS) {
        if (milliS > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(milliS));
    }

    void sleepS(int s) {
        if (s > 0)
            std::this_thread::sleep_for(std::chrono::seconds(s));
    }
};
