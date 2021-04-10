#ifndef RANDOMNUMGENERATOR_H
#define RANDOMNUMGENERATOR_H

#include <random>
#include <algorithm>

class RandomNumGenerator
{
public:
    RandomNumGenerator(int low, int high)
    : random_engine_{std::random_device{}()}
    , distribution_{low, high}
    {
    }
    int getNum()
    {
        return distribution_(random_engine_);
    }
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

#endif // RANDOMNUMGENERATOR_H
