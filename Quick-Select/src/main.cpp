#include <iostream>
#include "Algorithms.h"
#include "Experiment.h"
#include "Colors.h"
#include "StatisticCollector.h"
#include "fstream"
int main(int argc, char** argv) {
    if (std::string(argv[1]) == "--pres") {
        int n,k;
        std::cin >> n;
        std::cin >> k;

        int* arr_for_select = new int [n];
        int* arr_for_rand_select = new int[n];
        int* arr_for_bsearch = new int[n];
        for (int i = 0; i < n; i++) {
            std::cin >> arr_for_select[i];
            arr_for_bsearch[i] = arr_for_select[i];
            arr_for_rand_select[i] = arr_for_select[i];
        }
        bool flag = n<=50;
        std::cout << cMagenta << "select z zadana statystyka pozycyjna: " << cReset << k << std::endl;
        StatisticCollector stats;
        std::cout << "poczatkowy stan tablicy:\n";
        print(arr_for_select, 0, n);
        int result = select(arr_for_select, 0, n-1, k, stats, flag);
        std::cout << "wynik to: " << arr_for_select[result] << std::endl;
        std::cout << "tablica wynikowa: " << std::endl;
        print(arr_for_select, 0, n);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        insertion_sort(arr_for_select, 0, n-1);
        print(arr_for_select, 0, n);
        delete[] arr_for_select;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";




        std::cout << cMagenta << "random select z zadana statystyka pozycyjna: " << cReset << k << std::endl;

        std::cout << "poczatkowy stan tablicy:\n";
        print(arr_for_rand_select, 0, n);
        result = randomizedSelect(arr_for_rand_select, 0, n-1, k+1, stats, flag);
        std::cout << "wynik to: " << arr_for_rand_select[result] << std::endl;
        std::cout << "tablica wynikowa: " << std::endl;
        print(arr_for_rand_select, 0, n);
        std::cout << cGreen <<  "posortowana tablica:\n" << cReset;
        insertion_sort(arr_for_rand_select, 0, n-1);
        print(arr_for_rand_select, 0, n);
        delete[] arr_for_rand_select;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";






        std::cout << cMagenta << "binary search dla podanego elementu: " << cReset << arr_for_bsearch[n/3] << std::endl;

        std::cout << "poczatkowy stan tablicy:\n";
        insertion_sort(arr_for_bsearch, 0, n-1);
        print(arr_for_bsearch, 0, n);
        if (binarySearch(arr_for_bsearch, 0, n-1, arr_for_bsearch[n/3], stats)) {
            std::cout << "znaleziono element\n";
        } else {
            std::cout << "nie znaleziono elementu\n";
        }

        delete[] arr_for_bsearch;
        std::cout << cRed << "liczba porownan kluczy: " << cReset << stats.partialComps << std::endl;
        std::cout << cRed << "liczba przestawien kluczy: " << cReset << stats.partialSwaps << std::endl;
        stats.reset();
        std::cout << "\n\n\n";


    } else {
        Experiment experiment;/*
        experiment.select_experiment(100);
        experiment.random_select_experiment(100);
        experiment.select_k_experiment(100,3);
        experiment.select_k_experiment(100,5);
        experiment.select_k_experiment(100,7);
        experiment.select_k_experiment(100,9);*/
        experiment.binary_search_experiment(100);
    }
    return 0;
}
