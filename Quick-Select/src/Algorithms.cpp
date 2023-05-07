//
// Created by korycki on 07.05.2023.
//

#include "Algorithms.h"
int select(int *arr, int left, int right, int n, StatisticCollector& sc) { //int size??
    while (true) {
        if (left == right)
            return left;
        int pivotIndex = pivot(arr, left, right, sc);
        pivotIndex = selectPartition(arr, left, right, pivotIndex, n, sc);
        if (n == pivotIndex)
            return n;
        if (n < pivotIndex)
            right = pivotIndex - 1;
        else left = pivotIndex + 1;
    }
}

int selectPartition(int *arr, int left, int right, int pivotIndex, int n, StatisticCollector& sc) {
    int pivot = arr[pivotIndex];
    mySwap(arr, pivotIndex, right, sc);
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            mySwap(arr, storeIndex, i, sc);
            storeIndex++;
        }
        sc.partialComps++;
    }
    int storeIndexEq = storeIndex;
    for (int i = storeIndex; i < right; i++) {
        if (arr[i] == pivot) {
            mySwap(arr, storeIndexEq, i, sc);
            storeIndexEq++;
        }
        sc.partialComps++;
    }
    mySwap(arr, right, storeIndexEq, sc);
    if (n < storeIndex)
        return storeIndex;
    else if (n <= storeIndexEq)
        return n;
    return storeIndexEq;
}

int partition5(int *arr, int left, int right, StatisticCollector& sc) {
    int i = left + 1;
    int j;
    while (i <= right) {
        j = i;
        while (j > left && arr[j-1] && arr[j]) {
            mySwap(arr, j-1, j, sc);
            j--;
            sc.partialComps++;
        }
        sc.partialComps++;
        i++;
    }
    return (left + right)/2;
}

int pivot(int *arr, int left, int right, StatisticCollector& sc) {
    if (right - left < 5)
        return partition5(arr, left, right, sc);
    for (int i = left; i < right; i += 5) {
        int subRight = i + 4;
        if (subRight > right) {
            subRight = right;
        }
        sc.partialComps++;
        int median5 = partition5(arr, i, subRight, sc);
        mySwap(arr, median5, left + (i-left)/5, sc);
    }
    int mid = (right - left)/10 + left + 1;
    return select(arr, left, left + (right-left)/5, mid, sc);
}


void mySwap(int *arr, const int i1, const int i2, StatisticCollector& sc) {
    int tmp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = tmp;
    sc.partialSwaps++;
}

int pivotK(int *arr, int left, int right, int k, StatisticCollector& sc) {
    if (right - left < k)
        return partition5(arr, left, right, sc);
    for (int i = left; i < right; i += k) {
        int subRight = i + k - 1;
        if (subRight > right) {
            subRight = right;
        }
        sc.partialComps++;
        int median5 = partition5(arr, i, subRight, sc);
        mySwap(arr, median5, left + (i-left)/k, sc);
    }
    int mid = (right - left)/(k*2) + left + 1;
    return select(arr, left, left + (right-left)/k, mid, sc);
}

int selectK(int *arr, int left, int right, int n, int k, StatisticCollector& sc) { //int size??
    while (true) {
        if (left == right)
            return left;
        int pivotIndex = pivotK(arr, left, right, k, sc);
        pivotIndex = selectPartition(arr, left, right, pivotIndex, n, sc);
        if (n == pivotIndex)
            return n;
        if (n < pivotIndex)
            right = pivotIndex - 1;
        else left = pivotIndex + 1;
    }
}

int randomizedPartition(int *arr, int left, int right, StatisticCollector& sc) {
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(left, right);
    int pivotIndex = left;
    if (left < right) {
        pivotIndex = floor(dist(mt));
    }
    sc.partialComps++;
    mySwap(arr, pivotIndex, right, sc);
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= arr[right]) {
            mySwap(arr, i, j, sc);
            i++;
        }
        sc.partialComps++;
    }
    mySwap(arr, i, right, sc);
    return i;
}

int randomizedSelect(int *arr, int left, int right, int n, const int size, StatisticCollector& sc) {
    if (left == right) {
        return arr[left];
    }
    sc.partialComps++;
    int pivotIndex = randomizedPartition(arr, left, right. sc);
    int k = pivotIndex - left + 1;
    if (n == k) {
        return arr[pivotIndex];
    }
    else if (n < k) {
        return randomizedSelect(arr, left, pivotIndex - 1, n, size, sc);
    }
    else return randomizedSelect(arr, pivotIndex + 1, right, n - k, size, sc);
    sc.partialComps++;
    //printArr(arr, size)
}

bool binarySearch(int *arr, int left, int right, const int k, StatisticCollector& sc) {
    if (left > right)
        return false;
    sc.partialComps++;
    int mid = (left + right)/2;
    if (arr[mid] == k) {
        return true;
    }
    if (k < arr[mid]) {
        return binarySearch(arr, left, mid - 1, k, sc);
    }
    else return binarySearch(arr, mid + 1, right, k, sc);
}