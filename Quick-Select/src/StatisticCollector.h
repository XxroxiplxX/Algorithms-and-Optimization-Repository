//
// Created by korycki on 07.05.2023.
//

#ifndef QUICK_SELECT_STATISTICCOLLECTOR_H
#define QUICK_SELECT_STATISTICCOLLECTOR_H
struct StatisticCollector {
    long double comparisons = 0;
    long double swaps = 0;
    long double partialComps = 0;
    long double partialSwaps = 0;
    void reset() {partialSwaps = 0; partialComps = 0;}
    void reset_all() {
        comparisons = 0;
        swaps = 0;
        partialComps = 0;
        partialSwaps = 0;
    }
};

#endif //QUICK_SELECT_STATISTICCOLLECTOR_H
