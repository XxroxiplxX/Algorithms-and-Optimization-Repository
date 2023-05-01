//
// Created by piotrkali on 4/24/23.
//

#include "ManhattanState.h"
bool ManhattanState::operator<(const ManhattanState &state) {
    return manhattan_heuristic_cost(*this) + this->g_score < manhattan_heuristic_cost(state) + state.g_score;
}

std::list<ManhattanState*> ManhattanState::produce_neighbours() {
    std::list<ManhattanState*> neighbours;
    auto tmp_board = produce_matrix_view(this->board);
    int gap = find_gap(tmp_board);
    if (gap > 3) {
        //up
        swap(tmp_board, gap, gap-4);
        neighbours.push_back(new ManhattanState(tmp_board, this));
        swap(tmp_board, gap, gap-4);
    }
    if (gap < 12) {
        //down
        swap(tmp_board, gap, gap+4);
        neighbours.push_back(new ManhattanState(tmp_board, this));
        swap(tmp_board, gap, gap+4);
    }
    if (gap%4 != 0) {
        //left
        swap(tmp_board, gap, gap-1);
        neighbours.push_back(new ManhattanState(tmp_board, this));
        swap(tmp_board, gap, gap-1);
    }
    if (gap%4 != 3) {
        //right
        swap(tmp_board, gap, gap+1);
        neighbours.push_back(new ManhattanState(tmp_board, this));
        swap(tmp_board, gap, gap+1);
    }
    delete[] tmp_board;
    return neighbours;
}

ManhattanState::ManhattanState(uint8_t *_decoded_board, ManhattanState *_predecessor, move m, int gap) {
    switch (m) {
        case move::UP:
            std::swap(_decoded_board[gap], _decoded_board[gap - 4]);
            break;
        case move::DOWN:
            std::swap(_decoded_board[gap], _decoded_board[gap + 4]);
            break;
        case move::RIGHT:
            std::swap(_decoded_board[gap], _decoded_board[gap + 1]);
            break;
        case move::LEFT:
            std::swap(_decoded_board[gap], _decoded_board[gap - 1]);
            break;
    }
    this->board = compress_matrix(_decoded_board);
    this->predecessor = _predecessor;
    this->g_score = 0;
}

void ManhattanState::set_predecessor(ManhattanState *state) {
    this->predecessor = state;
}

State *ManhattanState::get_predecessor() {
    return this->predecessor;
}

ManhattanState::ManhattanState(uint8_t *_decoded_board, ManhattanState *_predecessor) {
    this->board = compress_matrix(_decoded_board);
    this->predecessor = _predecessor;
    this->g_score = 0;
}
