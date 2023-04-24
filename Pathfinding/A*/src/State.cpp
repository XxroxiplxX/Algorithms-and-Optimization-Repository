//
// Created by piotrkali on 4/22/23.
//

#include "State.h"

uint8_t* produce_matrix_view(uint64_t _board) {
    auto _board_arr = new uint8_t [16];
    for (int i = 15; i >= 0; i--) {
        _board_arr[i]= _board % 16;
        _board /= 16;
    }
    for (int i = 0; i < 16; i++) {
        //std::cout << _board_arr[i] << " ";
    }
    return _board_arr;
}
uint64_t compress_matrix(const uint8_t* _arr) {
    uint64_t _board = 0;
    uint64_t mult = 1;
    for (int i = SIZE - 1; i >= 0; i--) {
        _board += _arr[i]*mult;
        mult *= 16;
    }
    return _board;
}
int find_gap(const uint8_t* _arr) {
    for (int i = 0; i < SIZE; i++) {
        if (_arr[i] == 0) {
            return i;
        }
    }
    return -1;
}
std::list<State *> State::produce_neighbours() {
    std::list<State*> neighbours;
    auto tmp_board = produce_matrix_view(this->board);
    int gap = find_gap(tmp_board);
    if (gap > 3) {
        neighbours.push_back(new State(tmp_board, this, UP, gap));
    }
    if (gap < 12) {
        neighbours.push_back(new State(tmp_board, this, DOWN, gap));
    }
    if (gap%4 != 0) {
        neighbours.push_back(new State(tmp_board, this, LEFT, gap));
    }
    if (gap%4 != 3) {
        neighbours.push_back(new State(tmp_board, this, RIGHT, gap));
    }
    delete[] tmp_board;
    return neighbours;
}

State::State(uint8_t* _decoded_board, State* _predecessor, move m, int gap) {
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

bool State::operator==(const State &state) {
    return this->board == state.board;
}

void State::set_predecessor(State *state) {
    this->predecessor = state;
}

State *State::get_predecessor() {
    return this->predecessor;
}

int improved_manhattan_heuristic_cost(State state) {
    int dr = 0;
    int m_cost = 0;
    auto _tmp_board = produce_matrix_view(state.board);
    for (int i = 0; i < SIZE; i++) {

        if (_tmp_board[i] != 0) {
            int x_pos = i%4;
            int y_pos = i/4;
            int x_dest = (_tmp_board[i] - 1)%4;
            int y_dest = (_tmp_board[i] - 1)/4;
            m_cost += abs(x_pos - x_dest) + abs(y_pos - y_dest);
        }

        if (_tmp_board[i] != 0 and i%4 != 0) { //zera nigdy nie oplaca sie zamieniac z lewym sasiadem
            //left nbh exists
            if (_tmp_board[i] == i and _tmp_board[i - 1] == _tmp_board[i] + 1) {
                dr++; //ale jesli po lewej jest zero to dla 15 oplaca sie zmieniac
            }
            //case zero
            if (_tmp_board[i] == 15 and _tmp_board[i - 1] == 0) {
                dr++;
            }
        }
        if (i%4 != 3) {
            //right nbh exists
            if (_tmp_board[i] == i + 2 and _tmp_board[i + 1] + 1 == _tmp_board[i]) {
                dr++; //zero oplaca sie swapowac tylko jesli po prawej jest 15
            }
            //case zero
            if (_tmp_board[i] == 0 and _tmp_board[i + 1] == 15) {
                dr++;
            }
        }
        if (_tmp_board[i] != 0 and i > 3) {
            //uppon nbh exists
            if (_tmp_board[i] == i - 3 and _tmp_board[i - 4] == _tmp_board[i] + 4) {
                dr++;
            }
            //case zero
            if (_tmp_board[i] == 12 and _tmp_board[i + 4] == 8) {
                dr++;
            }
        }
        if (i < 12) {
            //down nbh exists
            if (_tmp_board[i] == i + 5 and _tmp_board[i + 4] == _tmp_board[i] - 4) {
                dr++;
            }
            //case zero
            if (_tmp_board[i] == 0 and _tmp_board[i + 4] == 12) {
                dr++;
            }
        }
    }
    delete[] _tmp_board;
    return dr + m_cost;
}

bool ManhattanState::operator<(const State &state) {
    return false;
}

std::list<ManhattanState *> ManhattanState::produce_neighbours() {
    return State::produce_neighbours();
}

bool ImprovedState::operator<(const State &state) {
    return improved_manhattan_heuristic_cost(*this) + this->g_score < improved_manhattan_heuristic_cost(state) + state.g_score;
}

std::list<ImprovedState *> ImprovedState::produce_neighbours() {
    return State::produce_neighbours();
}
