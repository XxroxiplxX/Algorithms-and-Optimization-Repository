//
// Created by piotrkali on 4/22/23.
//
#include "gtest/gtest.h"
#include "State.h"
#include "ImprovedState.h"
#include <iostream>
#include "cstdint"
#include "Logger.h"

using namespace Logging;
TEST(StateTest, HeuristicTest) {
    State state = State(0x123456789abcdef0);
    EXPECT_EQ(0, improved_manhattan_heuristic_cost(state));
    auto s = ImprovedState(1);
    auto p = ImprovedState(1);
    EXPECT_TRUE(s==p);

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
    std::cout << print_board(produce_matrix_view(n));
    EXPECT_TRUE(is_solvable(s));
    EXPECT_FALSE(is_solvable(n));
}