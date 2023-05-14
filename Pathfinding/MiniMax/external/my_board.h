#ifndef MINIMAX_my_board_H
#define MINIMAX_my_board_H
int min(int a, int b);
int max(int a, int b);

typedef struct { int board[5][5]; } my_board;

const int WIN_LENGTH = 28;
const int LOSE_LENGTH = 48;

int evaluate(my_board s);
int minmaxrec(my_board s, int depth, int a, int b, bool isMAX);
int minmax(my_board s, int depth, int player);

#endif //MINIMAX_my_board_H