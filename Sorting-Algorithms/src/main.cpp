#include <iostream>
#include "Algorithms.h"
#include "Experiment.h"
#include "Colors.h"
#include "StatisticCollector.h"
int main(int argc, char** argv) {
    if (std::string(argv[1]) == "--pres") {
        int n;
        std::cin >> n;
        int* arr_for_merge = new int[n];
        int* arr_for_ins = new int[n];
        int* arr_for_quick = new int[n];
        int* arr_for_dual_pivot = new int[n];
        int* arr_for_hybrid = new int[n];
        for (int i = 0; i < n; i++) {
            std::cin >> arr_for_merge[i];
            arr_for_ins[i] = arr_for_merge[i];
            arr_for_quick[i] = arr_for_merge[i];
            arr_for_dual_pivot[i] = arr_for_merge[i];
            arr_for_hybrid[i] = arr_for_merge[i];
        }
        bool flag = n<40;
        std::cout << cMagenta << "insertion sort:\n" << cReset;
        StatisticCollector stats;
        stats.insertion_sort(arr_for_ins, 0, n, flag);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        print(arr_for_ins, 0, n);
        delete[] arr_for_ins;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";


        std::cout << cMagenta << "merge sort:\n" << cReset;
        stats.mergeSort(arr_for_merge, 0, n, flag);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        print(arr_for_merge, 0, n);
        delete[] arr_for_merge;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";


        std::cout << cMagenta <<  "quick sort:\n" << cReset;
        stats.quick_sort(arr_for_quick, 0, n, flag);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        print(arr_for_quick, 0, n);
        delete[] arr_for_quick;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";


        std::cout << cMagenta << "dual pivot quick sort:\n" << cReset;
        stats.dualPivotQuickSort(arr_for_dual_pivot, 0, n, flag);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        print(arr_for_dual_pivot, 0, n);
        delete[] arr_for_dual_pivot;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";


        std::cout << cMagenta << "hybrid quick sort sort:\n" << cReset;
        stats.hybrid_quick_sort(arr_for_hybrid, 0, n-1, flag);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        print(arr_for_hybrid, 0, n);
        delete[] arr_for_hybrid;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        std::cout << "\n\n\n";

    } else {
        Experiment experiment;
        int k = 100;
            experiment.insertionExperiment(k);
            experiment.mergeExperiment(k);
            experiment.quickExperiment(k);
            experiment.dualPivotExperiment(k);
            experiment.hybridExperiment(k);
        
    }
    return 0;
}
