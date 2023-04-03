//
// Created by piotrkali on 4/3/23.
//

#ifndef SORTING_ALGORITHMS_GENERATOR_H
#define SORTING_ALGORITHMS_GENERATOR_H

#include <random>
class Generator {
    std::mt19937 mt;
public:
    Generator(){}
    int* produceRandomArray(int range);
};


#endif //SORTING_ALGORITHMS_GENERATOR_H
