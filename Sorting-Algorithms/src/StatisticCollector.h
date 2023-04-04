//
// Created by korycki on 30.03.2023.
//

#ifndef SORTING_ALGORITHMS_STATISTICCOLLECTOR_H
#define SORTING_ALGORITHMS_STATISTICCOLLECTOR_H


struct StatisticCollector {
    long long comparisons = 0;
    long long swaps = 0;
    long long partialComps = 0;
    long long partialSwaps = 0;
    void reset() {partialSwaps = 0; partialComps = 0;}
};


#endif //SORTING_ALGORITHMS_STATISTICCOLLECTOR_H
