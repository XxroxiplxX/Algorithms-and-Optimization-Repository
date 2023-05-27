//
// Created by piotrkali on 4/24/23.
//

#ifndef A_MANHATTANSTATE_H
#define A_MANHATTANSTATE_H

#include "State.h"
struct ManhattanState : public State{
    std::list<ManhattanState*> produce_neighbours();
    ManhattanState(uint8_t* _decoded_board, ManhattanState* _predecessor, move m, int gap);
    ManhattanState(uint64_t _board) {
        this->board = _board;
        this->g_score = 0;
        this->f_score = 0;
        this->h_score = 0;
    }
    ManhattanState(uint8_t* _decoded_board, ManhattanState* _predecessor);

    void set_predecessor(ManhattanState* state);
    State* get_predecessor();
    ~ManhattanState() {
        this->predecessor = nullptr;
    }
    ManhattanState* predecessor;
};

struct ManhattanComparer {
    bool operator () (ManhattanState* m1, ManhattanState* m2) {
        return m1->f_score > m2->f_score;
    }
};

#endif //A_MANHATTANSTATE_H
