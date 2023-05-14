//
// Created by korycki on 07.05.2023.
//

#include "Algorithms.h"
void print(int* arr, int low, int high) {
    for (int i = low; i < high; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int select(int *arr, int left, int right, int n, StatisticCollector& sc, bool presentation) {
    while (true) {
        if (left == right)
            return left;
        int pivotIndex = pivot(arr, left, right, sc);
        pivotIndex = selectPartition(arr, left, right, pivotIndex, n, sc);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivota = " << cReset << pivotIndex << std::endl;
            print(arr, left, right-1);
        }
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

int selectK(int *arr, int left, int right, int n, int k, StatisticCollector& sc, bool presentation) { //int size??
    while (true) {
        if (left == right)
            return left;
        int pivotIndex = pivotK(arr, left, right, k, sc);
        pivotIndex = selectPartition(arr, left, right, pivotIndex, n, sc);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivota = " << cReset << pivotIndex << std::endl;
            print(arr, left, right-1);
        }
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

int randomizedSelect(int *arr, int left, int right, int n,  StatisticCollector& sc, bool presentation) {
    if (left == right) {
        return left;
    }
    sc.partialComps++;
    int pivotIndex = randomizedPartition(arr, left, right, sc);
    if (presentation) {
        std::cout << cBlue << "po wybraniu pivota = " << cReset << pivotIndex << std::endl;
        print(arr, left, right-1);
    }
    int k = pivotIndex - left + 1;
    if (n == k) {
        return pivotIndex;
    }
    else if (n < k) {
        return randomizedSelect(arr, left, pivotIndex - 1, n,  sc, presentation);
    }
    else return randomizedSelect(arr, pivotIndex + 1, right, n - k,  sc, presentation);
    //sc.partialComps++;
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
        sc.partialComps++;
        return binarySearch(arr, left, mid - 1, k, sc);
    }
    else return binarySearch(arr, mid + 1, right, k, sc);
}

std::pair<int,int> dual_partition(int* arr, int low, int high, StatisticCollector& sc) {
    if (arr[low] > arr[high]) {
        swap(&arr[low], &arr[high]);
        sc.partialSwaps+=2;
    }
    sc.partialComps++;

    int j = low + 1;
    int g = high - 1, k = low + 1; //, p = arr[low], q = arr[high];
    int p = arr[select(arr, low, high, (high-low+1)/3, sc)];
    int q = arr[select(arr, low, high, (high-low+1)/3*2, sc)];
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

void dual_pivot_quick_sort_select(int* arr, int low, int high, StatisticCollector& sc, bool presentation) {
    if (low < high) {
        std::pair<int,int> p = dual_partition(arr, low, high, sc);
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivotow = (" << p.first << "," << p.second << ")" << cReset << std::endl;
            print(arr, low, high-1);
        }
        dual_pivot_quick_sort_select(arr, low, p.first - 1, sc, presentation);
        dual_pivot_quick_sort_select(arr, p.first + 1, p.second - 1, sc, presentation);
        dual_pivot_quick_sort_select(arr, p.second + 1, high, sc, presentation);
    }
}

int partition(int* arr, int low, int high, StatisticCollector& sc)
{
    int p = select(arr, low, high, (high-low+1)/2, sc);
    int x = arr[p];
}

void quick_sort_select(int* arr, int low,int high, StatisticCollector& sc, bool presentation)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high, sc);
        std::cout << "reukur\n";
        if (presentation) {
            std::cout << cBlue << "po wybraniu pivota = " << cReset << pivot << std::endl;
            print(arr, low, high-1);
        }
        quick_sort_select(arr, low, pivot-1, sc, presentation) ;
        quick_sort_select(arr, pivot + 1, high, sc, presentation) ;
    }
}
void insertion_sort(int* arr, int low, int n)
{

    for(int i=low+1;i<n+1;i++)
    {
        int val = arr[i] ;
        int j = i ;
        while (j>low && arr[j-1]>val)
        {
            arr[j]= arr[j-1] ;
            j-= 1;
        }
        arr[j]= val ;

    }

}