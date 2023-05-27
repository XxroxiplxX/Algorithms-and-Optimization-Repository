//
// Created by piotrkali on 4/24/23.
//

#include "ImprovedState.h"
bool ImprovedState::operator<(const ImprovedState &state) {
    return improved_manhattan_heuristic_cost(*this) + this->g_score < improved_manhattan_heuristic_cost(state) + state.g_score and this->board != state.board;
}

std::list<ImprovedState *> ImprovedState::produce_neighbours() {
    std::list<ImprovedState*> neighbours;
    auto tmp_board = produce_matrix_view(this->board);
    int gap = find_gap(tmp_board);
    if (gap > 3) {
        //up
        swap(tmp_board, gap, gap-4);
        neighbours.push_back(new ImprovedState(tmp_board, this));
        swap(tmp_board, gap, gap-4);
    }
    if (gap < 12) {
        //down
        swap(tmp_board, gap, gap+4);
        neighbours.push_back(new ImprovedState(tmp_board, this));
        swap(tmp_board, gap, gap+4);
    }
    if (gap%4 != 0) {
        //left
        swap(tmp_board, gap, gap-1);
        neighbours.push_back(new ImprovedState(tmp_board, this));
        swap(tmp_board, gap, gap-1);
    }
    if (gap%4 != 3) {
        //right
        swap(tmp_board, gap, gap+1);
        neighbours.push_back(new ImprovedState(tmp_board, this));
        swap(tmp_board, gap, gap+1);
    }
    delete[] tmp_board;
    return neighbours;
}

void ImprovedState::set_predecessor(ImprovedState *state) {
    this->predecessor = state;
}

State *ImprovedState::get_predecessor() {
    return this->predecessor;
}

ImprovedState::ImprovedState(uint8_t *_decoded_board, ImprovedState *_predecessor, move m, int gap) {
    switch (m) {
        case move::UP:
            swap(_decoded_board, gap, gap - 4);
            break;
        case move::DOWN:
            swap(_decoded_board, gap, gap + 4);
            break;
        case move::RIGHT:
            swap(_decoded_board, gap, gap + 1);
            break;
        case move::LEFT:
            swap(_decoded_board, gap, gap - 1);
            break;
    }
    this->board = compress_matrix(_decoded_board);
    this->predecessor = _predecessor;
    this->g_score = 0;
}

ImprovedState::ImprovedState(uint8_t *_decoded_board, ImprovedState *_predecessor) {
    this->board = compress_matrix(_decoded_board);
    this->predecessor = _predecessor;
    this->g_score = 0;
}
