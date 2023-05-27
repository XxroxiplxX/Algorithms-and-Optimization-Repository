//
// Created by korycki on 30.03.2023.
//

#include <iostream>
#include "Experiment.h"
#include <map>
void Experiment::insertionExperiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 10; n <= 200; n +=10) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 10; n <= 200; n +=10) {
            auto arr = generator.produceRandomArray(n);
            records[n].insertion_sort(arr, 0, n-1);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].partialSwaps = 0;
            records[n].partialComps = 0;
        }
    }
    std::ofstream swaps("../../data/insertion/insertion_sort_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/insertion/insertion_sort_comps" + std::to_string(repetitions) + ".csv");
    swaps << "n" << ";" << "swaps" << std::endl;
    comps << "n" << ";" << "comps" << std::endl;
    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();

}
#include "StatisticCollector.h"
void Experiment::mergeExperiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 10; n <= 200; n +=10) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 10; n <= 200; n +=10) {
            auto arr = generator.produceRandomArray(n);
            records[n].mergeSort(arr, 0, n-1);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps)/repetitions;
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].partialSwaps = 0;
            records[n].partialComps = 0;
        }
    }
    std::ofstream swaps("../../data/merge/merge_sort_small_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/merge/merge_sort_small_comps" + std::to_string(repetitions) + ".csv");
    swaps << "n" << ";" << "swaps" << std::endl;
    comps << "n" << ";" << "comps" << std::endl;
    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();

    std::map<int, StatisticCollector> bigRecords;
    for (int n = 1000; n <= 20000; n +=1000) {
        bigRecords[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 20000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            bigRecords[n].mergeSort(arr, 0, n-1);
            delete[] arr;
            bigRecords[n].swaps+=(double)(bigRecords[n].partialSwaps/repetitions);
            bigRecords[n].comparisons+=(double)(bigRecords[n].partialComps/repetitions);
            bigRecords[n].partialSwaps = 0;
            bigRecords[n].partialComps = 0;
        }
    }
    std::ofstream bigSwaps("../../data/merge/merge_sort_big_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream bigComps("../../data/merge/merge_sort_big_comps" + std::to_string(repetitions) + ".csv");
    bigSwaps << "n" << ";" << "swaps" << std::endl;
    bigComps << "n" << ";" << "comps" << std::endl;
    for (auto item : bigRecords) {
        bigSwaps << item.first << ";" << item.second.swaps << std::endl;
        bigComps << item.first << ";" << item.second.comparisons << std::endl;
    }
    bigSwaps.close();
    bigComps.close();
}

void Experiment::quickExperiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 10; n <= 200; n +=10) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 10; n <= 200; n +=10) {
            auto arr = generator.produceRandomArray(n);
            records[n].quick_sort(arr, 0, n-1);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].partialSwaps = 0;
            records[n].partialComps = 0;
        }
    }
    std::ofstream swaps("../../data/quick/quick_sort_small_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/quick/quick_sort_small_comps" + std::to_string(repetitions) + ".csv");
    swaps << "n" << ";" << "swaps" << std::endl;
    comps << "n" << ";" << "comps" << std::endl;
    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();

    std::map<int, StatisticCollector> bigRecords;
    for (int n = 1000; n <= 20000; n +=1000) {
        bigRecords[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 20000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            records[n].quick_sort(arr, 0, n-1);
            delete[] arr;
            bigRecords[n].swaps+=(bigRecords[n].partialSwaps/repetitions);
            bigRecords[n].comparisons+=(bigRecords[n].partialComps/repetitions);
            bigRecords[n].partialSwaps = 0;
            bigRecords[n].partialComps = 0;
        }
    }
    std::ofstream bigSwaps("../../data/quick/quick_sort_big_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream bigComps("../../data/quick/quick_sort_big_comps" + std::to_string(repetitions) + ".csv");
    bigSwaps << "n" << ";" << "swaps" << std::endl;
    bigComps << "n" << ";" << "comps" << std::endl;
    for (auto item : bigRecords) {
        bigSwaps << item.first << ";" << item.second.swaps << std::endl;
        bigComps << item.first << ";" << item.second.comparisons << std::endl;
    }
    bigSwaps.close();
    bigComps.close();
}

void Experiment::dualPivotExperiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 10; n <= 200; n +=10) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 10; n <= 200; n +=10) {
            auto arr = generator.produceRandomArray(n);
            records[n].dualPivotQuickSort(arr, 0, n-1);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].partialSwaps = 0;
            records[n].partialComps = 0;
        }
    }
    std::ofstream swaps("../../data/dual/dual_pivot_quick_sort_small_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/dual/dual_pivot_quick_sort_small_comps" + std::to_string(repetitions) + ".csv");
    swaps << "n" << ";" << "swaps" << std::endl;
    comps << "n" << ";" << "comps" << std::endl;
    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();

    std::map<int, StatisticCollector> bigRecords;
    for (int n = 1000; n <= 20000; n +=1000) {
        bigRecords[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 20000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            records[n].dualPivotQuickSort(arr, 0, n-1);
            delete[] arr;
            bigRecords[n].swaps+=(bigRecords[n].partialSwaps/repetitions);
            bigRecords[n].comparisons+=(bigRecords[n].partialComps/repetitions);
            bigRecords[n].partialSwaps = 0;
            bigRecords[n].partialComps = 0;
        }
    }
    std::ofstream bigSwaps("../../data/dual/dual_pivot_quick_sort_big_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream bigComps("../../data/dual/dual_pivot_quick_sort_big_comps" + std::to_string(repetitions) + ".csv");
    bigSwaps << "n" << ";" << "swaps" << std::endl;
    bigComps << "n" << ";" << "comps" << std::endl;
    for (auto item : bigRecords) {
        bigSwaps << item.first << ";" << item.second.swaps << std::endl;
        bigComps << item.first << ";" << item.second.comparisons << std::endl;
    }
    bigSwaps.close();
    bigComps.close();
}

void Experiment::hybridExperiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 10; n <= 200; n +=10) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 10; n <= 200; n +=10) {
            auto arr = generator.produceRandomArray(n);
            records[n].hybrid_quick_sort(arr, 0, n-1);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].partialSwaps = 0;
            records[n].partialComps = 0;
        }
    }
    std::ofstream swaps("../../data/hybrid/hybrid_quick_sort_small_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/hybrid/hybrid_quick_sort_small_comps" + std::to_string(repetitions) + ".csv");
    swaps << "n" << ";" << "swaps" << std::endl;
    comps << "n" << ";" << "comps" << std::endl;
    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();

    std::map<int, StatisticCollector> bigRecords;
    for (int n = 1000; n <= 20000; n +=1000) {
        bigRecords[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 20000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            records[n].hybrid_quick_sort(arr, 0, n-1);
            delete[] arr;
            bigRecords[n].swaps+=(bigRecords[n].partialSwaps/repetitions);
            bigRecords[n].comparisons+=(bigRecords[n].partialComps/repetitions);
            bigRecords[n].partialSwaps = 0;
            bigRecords[n].partialComps = 0;
        }
    }
    std::ofstream bigSwaps("../../data/hybird/hybrid_quick_sort_big_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream bigComps("../../data/hybrid/hybrid_quick_sort_big_comps" + std::to_string(repetitions) + ".csv");
    bigSwaps << "n" << ";" << "swaps" << std::endl;
    bigComps << "n" << ";" << "comps" << std::endl;
    for (auto item : bigRecords) {
        bigSwaps << item.first << ";" << item.second.swaps << std::endl;
        bigComps << item.first << ";" << item.second.comparisons << std::endl;
    }
    bigSwaps.close();
    bigComps.close();
}
