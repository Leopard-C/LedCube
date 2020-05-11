#pragma once
#include "./effect.h"


struct Function {
    double xCoefficient;
    double yCoefficient;
    double zCoefficient;
    double xPower; 
    double yPower;
    double zPower;
    double constTerm;
};


class FunctionGraphEffect {
public:
    bool setFunc(std::string& funcStr);

    
    virtual void show();
    virtual bool readFromFP(FILE* fp);
    
private:
    Function func;
};


