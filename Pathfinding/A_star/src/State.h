//
// Created by piotrkali on 4/22/23.
//

#ifndef A_STATE_H
#define A_STATE_H
#include <cstdint>
#include <memory>
#include <iostream>
#include <list>
#define SIZE 16
#define N 4
enum move {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NULL_MOVE
};
struct State {
    uint64_t board;
    int g_score;
    int h_score;
    int f_score;
    State(){}
    State(uint64_t _board) : board(_board), g_score(0){}
    ~State() = default;
    bool operator ==(const State& state) const;

private:
    //State* predecessor;
};


uint8_t* produce_matrix_view(uint64_t _board);
uint64_t compress_matrix(const uint8_t* _arr);
int find_gap(const uint8_t* _arr);
int manhattan_heuristic_cost(State state);
int improved_manhattan_heuristic_cost(State state);
void swap(uint8_t* arr, int i, int j);
void move_gap(uint8_t* _board, move m, int gap);
std::string print_board(uint8_t* board);
bool is_solvable(uint64_t board);


#endif //A_STATE_H
