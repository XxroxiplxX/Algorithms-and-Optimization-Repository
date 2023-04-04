//
// Created by piotrkali on 3/28/23.
//

#ifndef SORTING_ALGORITHMS_ALGORITHMS_H
#define SORTING_ALGORITHMS_ALGORITHMS_H

#include <utility>
#include "StatisticCollector.h"
void print(int* arr, int low, int high);
void swap(int* a, int* b);
void insertion_sort(int* arr, int low, int n,                  StatisticCollector& sc, bool presentation=false);
int partition(int* arr, int low, int high,                     StatisticCollector& sc);
void dualPivotQuickSort(int* arr, int low, int high,           StatisticCollector& sc, bool presentation=false);
void quick_sort(int* arr, int low, int high,                   StatisticCollector& sc, bool presentation=false);
void merge(int* arr, int l, int m, int r,                      StatisticCollector& sc);
void mergeSort(int* arr, int low, int high,                    StatisticCollector& sc, bool presentation=false);
void hybrid_quick_sort(int* arr, int low, int high,            StatisticCollector& sc, bool presentation=false);
std::pair<int,int> dual_partition(int* arr, int low, int high, StatisticCollector& sc);
#endif //SORTING_ALGORITHMS_ALGORITHMS_H
