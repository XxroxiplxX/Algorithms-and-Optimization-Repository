//
// Created by korycki on 30.03.2023.
//

#ifndef SORTING_ALGORITHMS_EXPERIMENT_H
#define SORTING_ALGORITHMS_EXPERIMENT_H

#include <fstream>
#include "Generator.h"
#include "StatisticCollector.h"
#include <map>
#include "Algorithms.h"
class Experiment {
    //std::ofstream output;
    Generator generator;
public:
    void insertionExperiment(int repetitions);
    void mergeExperiment(int repetitions);
    void quickExperiment(int repetitions);
    void dualPivotExperiment(int repetitions);
    void hybridExperiment(int repetitions);

};


#endif //SORTING_ALGORITHMS_EXPERIMENT_H
