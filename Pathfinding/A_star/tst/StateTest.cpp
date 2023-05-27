//
// Created by piotrkali on 4/22/23.
//
#include "gtest/gtest.h"
#include "State.h"
#include "ImprovedState.h"
#include <iostream>
#include "cstdint"
#include "Logger.h"
#include "Algorithm.h"
using namespace Logging;
TEST(StateTest, HeuristicTest) {
    State state = State(0x123456789abcdef0);
    EXPECT_EQ(0, improved_manhattan_heuristic_cost(state));
    auto s = ImprovedState(1);
    auto p = ImprovedState(1);
    EXPECT_TRUE(s==p);
    //EXPECT_FALSE(s<p);
    EXPECT_EQ(0, improved_manhattan_heuristic_cost(state));
    //uint8_t b[] = {1,2,3,4,0,5,6,7,8,9,10,11,12,13,14,15};
    //auto p = compress_matrix(b);

    //std::cout << improved_manhattan_heuristic_cost(&state) << std::endl;
}
TEST(StateTest, MoveTest) {

    ImprovedState* state = new ImprovedState(0x123456789ab0defc);
    auto nbhs = state->produce_neighbours();
    Logger logger("../../logs/MoveTest.log");
    logger.log("start:\n" + print_board(produce_matrix_view(state->board)) + "\n\n");
    for (auto n : nbhs) {
        logger.log("neighbour:\n" + print_board(produce_matrix_view(n->board)) + "\n\n");

    }
}
TEST(StateTest, validity) {
    uint64_t s = 0xc1a27b4e509f8d63;
    uint64_t n = 0x391feb46d0ac2785;
    //std::cout << print_board(produce_matrix_view(n));
    EXPECT_TRUE(is_solvable(s));
    EXPECT_FALSE(is_solvable(n));
}
TEST(StateTest, heuristic_function_monotonicity) {
    srand(time(nullptr));
    std::mt19937 generator(rand());
    std::uniform_int_distribution<int>distribution(0,4);
    auto uut_board = randomize_board(generator, distribution, 10);
    Logger logger("../../logs/improved.log");
        //Logger stats("../../logs/improved_k=" + std::to_string(repetitions) + ".csv");
        std::list<ManhattanState*> safe_delete;
        ManhattanState* start = new ManhattanState(uut_board);

        safe_delete.push_back(start);
        logger.log("initializing algorithm...");
        int i = a_star_search_manhattan(start, safe_delete, logger);
        //logger.log("number of states: ", i);
        logger.log("deallocating graph with size: ", safe_delete.size());
        for (auto& vertex : safe_delete) {
            delete vertex;
        }
        logger.log("memory deallocated\n");
        logger.close_logger();
        std::list<ManhattanState*> s;
        for (auto& nbh : start->produce_neighbours()) {
            nbh->f_score = rand()%100;
            std::cout << nbh->f_score << std::endl;

            //s.push_front(nbh);
            for (auto& i : nbh->produce_neighbours()) {
                i->f_score = rand()%100;
                std::cout << i->f_score << std::endl;
                //s.push_front(i);
            }
        }
        auto a = 0x0123456789abcdef;
        auto b = 0x124356789abcdef0;
        auto s1 = new ManhattanState(produce_matrix_view(a), nullptr);
        auto s2 = new ManhattanState(produce_matrix_view(b), nullptr);

        s1->f_score = 3;
        s2->f_score = 4;
        s.push_front(s1);
        s.push_front(s2);
        for (auto item: s) {
            std::cout << std::hex << item->board << " ";
        }
        std::cout << "\n";
        erease(s, a);
        for (auto item: s) {
            std::cout << std::hex << item->board << " ";
        }
        //EXPECT_TRUE(contains(s, a));

        //auto x = *s.begin();
        //std::cout  << std::endl << x->f_score;
}