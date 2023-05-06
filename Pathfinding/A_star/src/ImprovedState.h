//
// Created by piotrkali on 4/24/23.
//

#ifndef A_IMPROVEDSTATE_H
#define A_IMPROVEDSTATE_H

#include "State.h"
struct ImprovedState : public  State {
    std::list<ImprovedState*> produce_neighbours();
    ImprovedState(uint8_t* _decoded_board, ImprovedState* _predecessor, move m, int gap);
    ImprovedState(uint64_t board) {
        this->board = board;
        this->g_score = 0;
    }
    ImprovedState(uint8_t* _decoded_board, ImprovedState* _predecessor);
    bool operator <(const ImprovedState& state);
    void set_predecessor(ImprovedState* state);
    State* get_predecessor();
    ~ImprovedState() {
        this->predecessor = nullptr;
    }
    ImprovedState* predecessor;
};


#endif //A_IMPROVEDSTATE_H
