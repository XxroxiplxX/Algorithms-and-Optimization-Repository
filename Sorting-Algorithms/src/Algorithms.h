//
// Created by piotrkali on 3/28/23.
//

#ifndef SORTING_ALGORITHMS_ALGORITHMS_H
#define SORTING_ALGORITHMS_ALGORITHMS_H
void swap(int* a, int* b);
int partition(int* arr, int low, int high, int* lp);
void dualPivotQuickSort(int* arr, int low, int high);
void quickSort(int* arr, int low, int high);
void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int low, int high);
#endif //SORTING_ALGORITHMS_ALGORITHMS_H
