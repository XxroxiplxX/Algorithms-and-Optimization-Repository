//
// Created by piotrkali on 5/9/23.
//

#include "Experiment.h"
#include <map>
#include "StatisticCollector.h"
#include "Algorithms.h"
#include <fstream>
#include <iostream>
void Experiment::select_experiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 100; n <= 10000; n +=100) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 100; n <= 10000; n +=100) {
            auto arr = generator.produceRandomArray(n);
            int result = select(arr, 0, n-1, 5, records[n]);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].reset();
        }
        std::cout << "select    " <<  50*k/repetitions << "% done\n";
    }
    std::ofstream swaps("../../data/select/select_pos_5_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/select/select_pos_5_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();



    for (auto& item : records) {
        item.second.reset_all();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 100; n <= 10000; n +=100) {
            auto arr = generator.produceRandomArray(n);
            int result = select(arr, 0, n-1, n/2, records[n]);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].reset();
        }
        std::cout << "select    " <<  50+50*k/repetitions << "% done\n";
    }
    std::ofstream swaps_median("../../data/select/select_pos_median_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps_median("../../data/select/select_pos_median_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps_median.close();
    comps_median.close();

}

void Experiment::random_select_experiment(int repetitions) {
    std::map<int, StatisticCollector> records;
    for (int n = 100; n <= 10000; n +=100) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 100; n <= 10000; n +=100) {
            auto arr = generator.produceRandomArray(n);
            int result = randomizedSelect(arr, 0, n-1, 5, records[n]);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].reset();
        }
        std::cout << "random select    " <<  50*k/repetitions << "% done\n";
    }
    std::ofstream swaps("../../data/random_select/rand_select_pos_5_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/random_select/rand_select_pos_5_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();



    for (auto& item : records) {
        item.second.reset_all();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 100; n <= 10000; n +=100) {
            auto arr = generator.produceRandomArray(n);
            int result = randomizedSelect(arr, 0, n-1, n/2, records[n]);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].reset();
        }
        std::cout << "random select    " <<  50+50*k/repetitions << "% done\n";
    }
    std::ofstream swaps_median("../../data/random_select/rand_select_pos_median_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps_median("../../data/random_select/rand_select_pos_median_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps_median.close();
    comps_median.close();
}

void Experiment::select_k_experiment(int repetitions, int param) {
    std::map<int, StatisticCollector> records;
    for (int n = 100; n <= 10000; n +=100) {
        records[n] = StatisticCollector();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 100; n <= 10000; n +=100) {
            auto arr = generator.produceRandomArray(n);
            int result = selectK(arr, 0, n-1, 5, param, records[n]);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].reset();
        }
        std::cout << "select " << param << "   " <<  50*k/repetitions << "% done\n";
    }
    std::ofstream swaps("../../data/select" + std::to_string(param) + "/select_pos_5_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps("../../data/select" + std::to_string(param) + "/select_pos_5_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps.close();
    comps.close();



    for (auto& item : records) {
        item.second.reset_all();
    }

    for (int k = 0; k < repetitions; k++) {
        for (int n = 100; n <= 10000; n +=100) {
            auto arr = generator.produceRandomArray(n);
            int result = selectK(arr, 0, n-1, n/2, param, records[n]);
            delete[] arr;
            records[n].swaps+=(records[n].partialSwaps/repetitions);
            records[n].comparisons+=(records[n].partialComps/repetitions);
            records[n].reset();
        }
        std::cout << "select    " <<  50+50*k/repetitions << "% done\n";
    }
    std::ofstream swaps_median("../../data/select" + std::to_string(param) + "/select_pos_median_swaps" + std::to_string(repetitions) + ".csv");
    std::ofstream comps_median("../../data/select" + std::to_string(param) + "/select_pos_median_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        swaps << item.first << ";" << item.second.swaps << std::endl;
        comps << item.first << ";" << item.second.comparisons << std::endl;
    }
    swaps_median.close();
    comps_median.close();

}

void Experiment::binary_search_experiment(int repetitions) {

    std::map<int, StatisticCollector> records;
    for (int n = 1000; n <= 100000; n +=1000) {
        records[n] = StatisticCollector();
    }
    //blisko poczatku
    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 100000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            bool result = binarySearch(arr, 0, n-1, arr[10], records[n]);
            delete[] arr;

            records[n].comparisons+=(records[n].partialComps/repetitions);
            //std::cout << records[n].partialComps << std::endl;
            records[n].partialComps = 0;
        }
        std::cout << "bsearch    " <<  25*k/repetitions << "% done\n";
    }
    std::ofstream comps_begin("../../data/binary_search/bsearch_begin_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        //std::cout << item.second.comparisons << std::endl;
        comps_begin << item.first << ";" << item.second.comparisons << std::endl;
    }
    comps_begin.close();

    for (auto& item : records) {
        item.second.reset_all();
    }

    //blisko srodka
    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 100000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            bool result = binarySearch(arr, 0, n-1, arr[n/2+6], records[n]);
            delete[] arr;

            records[n].comparisons+=(records[n].partialComps/repetitions);

            records[n].partialComps = 0;
        }
        std::cout << "bsearch    " <<  25+25*k/repetitions << "% done\n";
    }
    std::ofstream comps_mid("../../data/binary_search/bsearch_mid_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        comps_mid << item.first << ";" << item.second.comparisons << std::endl;
    }
    comps_mid.close();

    for (auto& item : records) {
        item.second.reset_all();
    }


    //blisko konca
    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 100000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            bool result = binarySearch(arr, 0, n-1, arr[n - 15], records[n]);
            delete[] arr;

            records[n].comparisons+=(records[n].partialComps/repetitions);

            records[n].partialComps = 0;
        }
        std::cout << "bsearch    " <<  50+25*k/repetitions << "% done\n";
    }
    std::ofstream comps_end("../../data/binary_search/bsearch_end_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        comps_mid << item.first << ";" << item.second.comparisons << std::endl;
    }
    comps_mid.close();

    for (auto& item : records) {
        item.second.reset_all();
    }



    //losowo
    for (int k = 0; k < repetitions; k++) {
        for (int n = 1000; n <= 100000; n +=1000) {
            auto arr = generator.produceRandomArray(n);
            bool result = binarySearch(arr, 0, n-1, generator.get_random_key_pos(n), records[n]);
            delete[] arr;

            records[n].comparisons+=(records[n].partialComps/repetitions);

            records[n].partialComps = 0;
        }
        std::cout << "bsearch    " <<  75+25*k/repetitions << "% done\n";
    }
    std::ofstream comps_random("../../data/binary_search/bsearch_random_comps" + std::to_string(repetitions) + ".csv");

    for (auto item : records) {
        comps_random << item.first << ";" << item.second.comparisons << std::endl;
    }
    comps_mid.close();
}
