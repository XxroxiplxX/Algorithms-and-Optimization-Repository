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
enum move {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct State {
    uint64_t board;
    int g_score;
    State(uint64_t _board) : board(_board), g_score(0), predecessor(nullptr) {}
    State(uint8_t* _decoded_board, State* _predecessor, move m, int gap);
    std::list<State*> produce_neighbours();
    ~State() = default;
    bool operator ==(const State& state);
    void set_predecessor(State* state);
    State* get_predecessor();
private:
    State* predecessor;
};
struct ManhattanState : public State{
    std::list<ManhattanState*> produce_neighbours();
    bool operator <(const State& state);
};
struct ImprovedState : public  State {
    std::list<ImprovedState*> produce_neighbours();
    bool operator <(const State& state);
};
uint8_t* produce_matrix_view(uint64_t _board);
uint64_t compress_matrix(const uint8_t* _arr);
int find_gap(const uint8_t* _arr);
int manhattan_heuristic_cost(State* state);
int improved_manhattan_heuristic_cost(State state);
#endif //A_STATE_H
