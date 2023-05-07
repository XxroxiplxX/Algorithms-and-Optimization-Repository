//
// Created by korycki on 07.05.2023.
//

#ifndef QUICK_SELECT_ALGORITHMS_H
#define QUICK_SELECT_ALGORITHMS_H
#include "StatisticCollector.h"
#include <random>
int partition5(int *arr, int left, int right,                               StatisticCollector& sc);
int selectPartition(int *arr, int left, int right, int pivotIndex, int n,   StatisticCollector& sc);
int select(int *arr, int left, int right, int n,                            StatisticCollector& sc);
int pivot(int *arr, int left, int right,                                    StatisticCollector& sc);
void mySwap(int *arr, const int i1, const int i2,                           StatisticCollector& sc);
int pivotK(int *arr, int left, int right, int k,                            StatisticCollector& sc);
int selectK(int *arr, int left, int right, int n, int k,                    StatisticCollector& sc);
int randomizedPartition(int *arr, int left, int right,                      StatisticCollector& sc);
int randomizedSelect(int *arr, int left, int right, int n, const int size,  StatisticCollector& sc);
bool binarySearch(int *arr, int left, int right, const int k,               StatisticCollector& sc);
#endif //QUICK_SELECT_ALGORITHMS_H
