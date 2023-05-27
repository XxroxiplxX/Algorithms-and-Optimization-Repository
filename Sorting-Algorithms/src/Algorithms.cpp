//
// Created by korycki on 30.03.2023.
//
#include <iostream>
#include "Algorithms.h"
#include "Colors.h"
#include "StatisticCollector.h"
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print(int* arr, int low, int high) {
    for (int i = low; i < high; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
void StatisticCollector::insertion_sort(int* arr, int low, int n, bool presentation)
{

    for(int i=low+1;i<n+1;i++)
    {
        int val = arr[i] ;
        partialSwaps++;
        int j = i ;
        while (j>low && arr[j-1]>val)
        {
            partialComps++;
            arr[j]= arr[j-1] ;
            partialSwaps++;
            j-= 1;
        }
        partialComps++;
        arr[j]= val ;
        partialSwaps++;
        if (presentation) {
            std::cout << cBlue << "po wstawieniu\n" << cReset;
            print(arr, low, n-1);
        }
    }

}



int StatisticCollector::partition(int* arr, int low, int high)
{
    int pivot = arr[high] ;
    partialSwaps++;
    int i ,j;
    i = low;
    j = low;

    for (int i = low; i < high; i++)
    {
        if(arr[i]<pivot)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j += 1;
            partialComps+=3;
        }
        partialComps++;
    }

    int temp = arr[j];
    arr[j] = arr[high];
    arr[high] = temp;
    partialSwaps+=3;

    return j;
}





void StatisticCollector::quick_sort(int* arr, int low,int high, bool presentation)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivota = " << cReset << pivot << std::endl;
            print(arr, low, high-1);
        }
        quick_sort(arr, low, pivot-1,  presentation) ;
        quick_sort(arr, pivot + 1, high,  presentation) ;
    }
}



void StatisticCollector::hybrid_quick_sort(int* arr, int low, int high, bool presentation)
{
    while (low < high)
    {

        if (high-low + 1 < 10)
        {
            insertion_sort(arr, low, high,  presentation);
            break;
        }

        else

        {
            int pivot = partition(arr, low, high) ;

            if (presentation) {
                std::cout << cBlue << "po wybraniu pivota = " << cReset << pivot << std::endl;
                print(arr, low, high-1);
            }

            if (pivot-low<high-pivot)
            {
                hybrid_quick_sort(arr, low, pivot - 1,  presentation);
                low = pivot + 1;
            }
            else
            {



                hybrid_quick_sort(arr, pivot + 1, high,  presentation);
                high = pivot-1;
            }

        }

    }
}
void StatisticCollector::merge(int* arr, int l, int m, int r)
{

    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
        partialSwaps++;

    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
        partialSwaps++;
    }


    int i = 0, j = 0;

    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            this->partialComps++;
            arr[k] = L[i];
            partialSwaps++;
            i++;
        }
        else {
            this->partialComps++;
            arr[k] = R[j];
            partialSwaps++;
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        partialSwaps++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        partialSwaps++;
        j++;
        k++;
    }
}


void StatisticCollector::mergeSort(int* arr, int l, int r, bool presentation)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, presentation);
        mergeSort(arr, m + 1, r, presentation);
        merge(arr, l, m, r);
        if (presentation) {
            std::cout << cBlue << "po mergowaniu\n" << cReset;
            print(arr, l, r-1);
        }
    }
}
std::pair<int,int> StatisticCollector::dual_partition(int* arr, int low, int high) {
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
        partialSwaps+=2;
    }
    partialComps++;

    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    partialSwaps+=2;
    while (k <= g) {

        if (arr[k] < p) {
            swap(&arr[k], &arr[j]);
            partialSwaps++;
            j++;
        }
        else if (arr[k] >= q) {
            while (arr[g] > q && k < g) {
                g--;
                partialComps++;
            }
            partialComps++;
            swap(&arr[k], &arr[g]);
            partialSwaps++;
            g--;
            if (arr[k] < p) {
                swap(&arr[k], &arr[j]);
                partialSwaps++;
                j++;
            }
            partialComps++;
        }
        partialComps++;
        k++;
    }
    j--;
    g++;

    swap(&arr[low], &arr[j]);
    swap(&arr[high], &arr[g]);
    partialSwaps+=2;

    return std::pair<int,int>(j,g);
}
void StatisticCollector::dualPivotQuickSort(int* arr, int low, int high,  bool presentation) {
    if (low < high) {
        std::pair<int,int> p = dual_partition(arr, low, high);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivotow = (" << p.first << "," << p.second << ")" << cReset << std::endl;
            print(arr, low, high-1);
        }
        dualPivotQuickSort(arr, low, p.first - 1,  presentation);
        dualPivotQuickSort(arr, p.first + 1, p.second - 1,  presentation);
        dualPivotQuickSort(arr, p.second + 1, high, presentation);
    }
}