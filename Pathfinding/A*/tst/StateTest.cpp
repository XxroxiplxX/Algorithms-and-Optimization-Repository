//
// Created by piotrkali on 4/22/23.
//
#include "gtest/gtest.h"
#include "State.h"
#include <iostream>
#include "cstdint"
TEST(StateTest, HeuristicTest) {
    State state = State(0x123456789abcdef0);
    EXPECT_EQ(0, improved_manhattan_heuristic_cost(state));
    //uint8_t b[] = {1,2,3,4,0,5,6,7,8,9,10,11,12,13,14,15};
    //auto p = compress_matrix(b);

    //std::cout << improved_manhattan_heuristic_cost(&state) << std::endl;
}