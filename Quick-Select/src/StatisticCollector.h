//
// Created by korycki on 07.05.2023.
//

#ifndef QUICK_SELECT_STATISTICCOLLECTOR_H
#define QUICK_SELECT_STATISTICCOLLECTOR_H
struct StatisticCollector {
    long long comparisons = 0;
    long long swaps = 0;
    long long partialComps = 0;
    long long partialSwaps = 0;
    void reset() {partialSwaps = 0; partialComps = 0;}
};

#endif //QUICK_SELECT_STATISTICCOLLECTOR_H
