//
// Created by piotrkali on 5/9/23.
//

#ifndef QUICK_SELECT_GENERATOR_H
#define QUICK_SELECT_GENERATOR_H


#include <random>
#include <ctime>

class Generator {
    std::mt19937 mt;

public:
    Generator(){srand(time(nullptr)); mt = std::mt19937 (rand());}
    int* produceRandomArray(int range);
    int get_random_key_pos(int n);
};


#endif //QUICK_SELECT_GENERATOR_H
