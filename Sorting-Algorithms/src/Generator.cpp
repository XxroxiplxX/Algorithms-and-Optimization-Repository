//
// Created by piotrkali on 4/3/23.
//

#include "Generator.h"

int *Generator::produceRandomArray(int range) {
    auto distro = std::uniform_int_distribution<int>(0, 2*range - 1);
    int* arr = new int[range];
    for (int i = 0; i < range; i++) {
        arr[i] = distro(mt);
    }

    return arr;
}
