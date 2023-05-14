//
// Created by korycki on 07.05.2023.
//

#ifndef QUICK_SELECT_ALGORITHMS_H
#define QUICK_SELECT_ALGORITHMS_H
#include "StatisticCollector.h"
#include <random>
#include <ctime>
#include <iostream>
#include "Colors.h"
void insertion_sort(int* arr, int low, int n);
void print(int* arr, int low, int high);
int partition5(int *arr, int left, int right,                               StatisticCollector& sc);
int selectPartition(int *arr, int left, int right, int pivotIndex, int n,   StatisticCollector& sc);
int select(int *arr, int left, int right, int n,                            StatisticCollector& sc, bool presentation=false);
int pivot(int *arr, int left, int right,                                    StatisticCollector& sc);
void mySwap(int *arr, const int i1, const int i2,                           StatisticCollector& sc);
int pivotK(int *arr, int left, int right, int k,                            StatisticCollector& sc);
int selectK(int *arr, int left, int right, int n, int k,                    StatisticCollector& sc, bool presentation=false);
int randomizedPartition(int *arr, int left, int right,                      StatisticCollector& sc);
int randomizedSelect(int *arr, int left, int right, int n,                  StatisticCollector& sc, bool presentation=false);
bool binarySearch(int *arr, int left, int right, const int k,               StatisticCollector& sc);
std::pair<int,int> dual_partition(int* arr, int low, int high,              StatisticCollector& sc);
int partition(int* arr, int low, int high,                                  StatisticCollector& sc);
void quick_sort_select(int *arr, int left, int right,                       StatisticCollector& sc, bool presentation=false);
void dual_pivot_quick_sort_select(int *arr, int left, int right,            StatisticCollector& sc, bool presentation=false);
#endif //QUICK_SELECT_ALGORITHMS_H
