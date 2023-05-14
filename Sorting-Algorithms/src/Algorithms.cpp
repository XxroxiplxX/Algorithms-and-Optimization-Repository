//
// Created by korycki on 30.03.2023.
//
#include <iostream>
#include "Algorithms.h"
#include "Colors.h"
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
void insertion_sort(int* arr, int low, int n, StatisticCollector& sc, bool presentation)
{

    for(int i=low+1;i<n+1;i++)
    {
        int val = arr[i] ;
        sc.partialSwaps++;
        int j = i ;
        while (j>low && arr[j-1]>val)
        {
            sc.partialComps++;
            arr[j]= arr[j-1] ;
            sc.partialSwaps++;
            j-= 1;
        }
        sc.partialComps++;
        arr[j]= val ;
        sc.partialSwaps++;
        if (presentation) {
            std::cout << cBlue << "po wstawieniu\n" << cReset;
            print(arr, low, n-1);
        }
    }

}



int partition(int* arr, int low, int high, StatisticCollector& sc)
{
    int pivot = arr[high] ;
    sc.partialSwaps++;
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
            sc.partialComps+=3;
        }
        sc.partialComps++;
    }

    int temp = arr[j];
    arr[j] = arr[high];
    arr[high] = temp;
    sc.partialSwaps+=3;

    return j;
}





void quick_sort(int* arr, int low,int high, StatisticCollector& sc, bool presentation)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high, sc);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivota = " << cReset << pivot << std::endl;
            print(arr, low, high-1);
        }
        quick_sort(arr, low, pivot-1, sc, presentation) ;
        quick_sort(arr, pivot + 1, high, sc, presentation) ;
    }
}



void hybrid_quick_sort(int* arr, int low, int high, StatisticCollector& sc, bool presentation)
{
    while (low < high)
    {

        if (high-low + 1 < 10)
        {
            insertion_sort(arr, low, high, sc, presentation);
            break;
        }

        else

        {
            int pivot = partition(arr, low, high, sc) ;

            if (presentation) {
                std::cout << cBlue << "po wybraniu pivota = " << cReset << pivot << std::endl;
                print(arr, low, high-1);
            }

            if (pivot-low<high-pivot)
            {
                hybrid_quick_sort(arr, low, pivot - 1, sc, presentation);
                low = pivot + 1;
            }
            else
            {



                hybrid_quick_sort(arr, pivot + 1, high, sc, presentation);
                high = pivot-1;
            }

        }

    }
}
void merge(int* arr, int l, int m, int r, StatisticCollector& sc)
{

    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
        sc.partialSwaps++;
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
        sc.partialSwaps++;
    }


    int i = 0, j = 0;

    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            sc.partialComps++;
            arr[k] = L[i];
            sc.partialSwaps++;
            i++;
        }
        else {
            sc.partialComps++;
            arr[k] = R[j];
            sc.partialSwaps++;
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        sc.partialSwaps++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        sc.partialSwaps++;
        j++;
        k++;
    }
}


void mergeSort(int* arr, int l, int r, StatisticCollector& sc, bool presentation)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m,sc, presentation);
        mergeSort(arr, m + 1, r,sc, presentation);
        merge(arr, l, m, r,sc);
        if (presentation) {
            std::cout << cBlue << "po mergowaniu\n" << cReset;
            print(arr, l, r-1);
        }
    }
}
std::pair<int,int> dual_partition(int* arr, int low, int high, StatisticCollector& sc) {
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
        sc.partialSwaps+=2;
    }
    sc.partialComps++;

    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    sc.partialSwaps+=2;
    while (k <= g) {

        if (arr[k] < p) {
            swap(&arr[k], &arr[j]);
            sc.partialSwaps++;
            j++;
        }
        else if (arr[k] >= q) {
            while (arr[g] > q && k < g) {
                g--;
                sc.partialComps++;
            }
            sc.partialComps++;
            swap(&arr[k], &arr[g]);
            sc.partialSwaps++;
            g--;
            if (arr[k] < p) {
                swap(&arr[k], &arr[j]);
                sc.partialSwaps++;
                j++;
            }
            sc.partialComps++;
        }
        sc.partialComps++;
        k++;
    }
    j--;
    g++;

    swap(&arr[low], &arr[j]);
    swap(&arr[high], &arr[g]);
    sc.partialSwaps+=2;

    return std::pair<int,int>(j,g);
}
void dualPivotQuickSort(int* arr, int low, int high, StatisticCollector& sc, bool presentation) {
    if (low < high) {
        std::pair<int,int> p = dual_partition(arr, low, high, sc);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivotow = (" << p.first << "," << p.second << ")" << cReset << std::endl;
            print(arr, low, high-1);
        }
        dualPivotQuickSort(arr, low, p.first - 1, sc, presentation);
        dualPivotQuickSort(arr, p.first + 1, p.second - 1, sc, presentation);
        dualPivotQuickSort(arr, p.second + 1, high, sc, presentation);
    }
}