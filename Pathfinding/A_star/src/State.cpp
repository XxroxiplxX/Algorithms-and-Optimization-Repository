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




bool State::operator==(const State &state) const{
    return this->board == state.board;
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
int manhattan_heuristic_cost(State state) {

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

    }
    delete[] _tmp_board;
    return m_cost;
}
void swap(uint8_t* arr, int i, int j) {
    auto tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
std::string print_board(uint8_t* board) {
    std::string out = "";
    for (int i = 0; i < SIZE; i++) {
        out += std::to_string(board[i]);
        out += "   ";
        if (i%4 == 3) {
            out += "\n";
        }
    }
    return out;
}
void move_gap(uint8_t* _board, move m, int gap) {
    switch(m) {
        case UP:
            swap(_board, gap, gap-4);
            break;
        case DOWN:
            swap(_board, gap, gap+4);
            break;
        case RIGHT:
            swap(_board, gap, gap+1);
            break;
        case LEFT:
            swap(_board, gap, gap-1);
            break;
    }
}


int get_inv_count(int* arr)
{
    int inv_count = 0;
    for (int i = 0; i < N * N - 1; i++)
    {
        for (int j = i + 1; j < N * N; j++)
        {
            // count pairs(arr[i], arr[j]) such that
            // i < j but arr[i] > arr[j]
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}

// find Position of blank from bottom
int find_gap_position(int puzzle[N][N])
{
    // start from bottom-right corner of matrix
    for (int i = N - 1; i >= 0; i--)
        for (int j = N - 1; j >= 0; j--)
            if (puzzle[i][j] == 0)
                return N - i;
}


bool is_solvable(uint64_t board)
{
    auto tmp = produce_matrix_view(board);
    int puzzle[N][N];
    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            puzzle[i][j] = (int)tmp[c];
            c++;
        }
    }
    delete[] tmp;
    // Count inversions in given puzzle
    int invCount = get_inv_count((int*)puzzle);

    // If grid is odd, return true if inversion
    // count is even.
    if (N & 1)
        return !(invCount & 1);

    else     // grid is even
    {
        int pos = find_gap_position(puzzle);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}