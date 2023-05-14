//
// Created by piotrkali on 5/9/23.
//

#ifndef QUICK_SELECT_EXPERIMENT_H
#define QUICK_SELECT_EXPERIMENT_H

#include "Generator.h"
class Experiment {
    Generator generator;
public:
    void select_experiment(int repetitions);
    void random_select_experiment(int repetitions);
    void select_k_experiment(int repetitions, int param);
    void binary_search_experiment(int repetitions);
};


#endif //QUICK_SELECT_EXPERIMENT_H
