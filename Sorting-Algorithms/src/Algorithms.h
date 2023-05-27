//
// Created by piotrkali on 3/28/23.
//

#ifndef SORTING_ALGORITHMS_ALGORITHMS_H
#define SORTING_ALGORITHMS_ALGORITHMS_H
#include <utility>
struct StatisticCollector {
    long double comparisons = 0;
    long double swaps = 0;
    long double partialComps = 0;
    long double partialSwaps = 0;
    void reset() {partialSwaps = 0; partialComps = 0;}
    void merge(int* arr, int l, int m, int r                      );
    void mergeSort(int* arr, int low, int high,                    bool presentation=false);
    void insertion_sort(int* arr, int low, int n,                  bool presentation=false);
    int partition(int* arr, int low, int high                    );
    void dualPivotQuickSort(int* arr, int low, int high,            bool presentation=false);
    void quick_sort(int* arr, int low, int high,                   bool presentation=false);
    void hybrid_quick_sort(int* arr, int low, int high,             bool presentation=false);
    std::pair<int,int> dual_partition(int* arr, int low, int high);
};
void print(int* arr, int low, int high);
void swap(int* a, int* b);

#endif //SORTING_ALGORITHMS_ALGORITHMS_H
