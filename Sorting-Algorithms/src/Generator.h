//
// Created by piotrkali on 4/3/23.
//

#ifndef SORTING_ALGORITHMS_GENERATOR_H
#define SORTING_ALGORITHMS_GENERATOR_H

#include <random>
#include <ctime>

class Generator {
    std::mt19937 mt;

public:
    Generator(){srand(time(nullptr)); mt = std::mt19937 (rand());}
    int* produceRandomArray(int range);
};


#endif //SORTING_ALGORITHMS_GENERATOR_H
