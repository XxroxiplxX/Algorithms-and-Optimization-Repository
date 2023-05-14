#include " my_board.h"
int min(int a, int b)
{
  if (a < b) 
  {
    return a;
  }
  else
  {
    return b;
  }

}
int max(int a, int b)
{
  if (a < b) 
  {
    return b;
  }
  else
  {
    return a;
  }

}



int evaluate(state s)
{
    for (int i = 0; i < WIN_LENGTH; i++)
    {
        if ((s.board[win[i][0][0]][win[i][0][1]] == 2) && (s.board[win[i][1][0]][win[i][1][1]] == 2) &&
            (s.board[win[i][2][0]][win[i][2][1]] == 2) && (s.board[win[i][3][0]][win[i][3][1]] == 2))
        {
            return MIN;
        }
        if ((s.board[win[i][0][0]][win[i][0][1]] == 1) && (s.board[win[i][1][0]][win[i][1][1]] == 1) &&
            (s.board[win[i][2][0]][win[i][2][1]] == 1) && (s.board[win[i][3][0]][win[i][3][1]] == 1))
        {
            return MAX;
        }
    }
    for (int i = 0; i < LOSE_LENGTH; i++)
    {
        if ((s.board[lose[i][0][0]][lose[i][0][1]] == 2) && (s.board[lose[i][1][0]][lose[i][1][1]] == 2) &&
            (s.board[lose[i][2][0]][lose[i][2][1]] == 2))
        {
            return MAX;
        }
                if ((s.board[lose[i][0][0]][lose[i][0][1]] == 1) && (s.board[lose[i][1][0]][lose[i][1][1]] == 1) &&
            (s.board[lose[i][2][0]][lose[i][2][1]] == 1))
        {
            return MIN;
        }
    }

    int eval = 0;
    for (int i = 0; i < WIN_LENGTH; i++)
    {
        if ((s.board[win[i][0][0]][win[i][0][1]] != 2) && (s.board[win[i][1][0]][win[i][1][1]] != 2) &&
            (s.board[win[i][2][0]][win[i][2][1]] != 2) && (s.board[win[i][3][0]][win[i][3][1]] != 2))
        {
            eval++;
        }
        if ((s.board[win[i][0][0]][win[i][0][1]] != 1) && (s.board[win[i][1][0]][win[i][1][1]] != 1) &&
            (s.board[win[i][2][0]][win[i][2][1]] != 1) && (s.board[win[i][3][0]][win[i][3][1]] != 1))
        {
            eval--;
        }
    }
    return eval;
}

int minmaxrec(state s, int depth, int a, int b, bool isMAX)
{
    int value = evaluate(s);
    if (depth == 0 || value == MIN || value == MAX)
        return value;

    bool prune = false;

    if (isMAX)
    {
        int maxEval = MIN;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (s.board[i][j] == 0)
                {
                    my_board nextState = s;
                    nextState.board[i][j] = 1;

                    int eval = minmaxrec(nextState, depth - 1, a, b, false);
                    maxEval = max(maxEval, eval);
                    a = max(a, eval);

                    if (b <= a)
                    {
                        prune = true;
                        break;
                    }
                }
            }
            if (prune) { break; }
        }
        return maxEval;
    }
    else
    {
        int minEval = MAX;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (s.board[i][j] == 0)
                {
                    my_board nextState = s;
                    nextState.board[i][j] = 2;

                    int eval = minmaxrec(nextState, depth - 1, a, b, true);
                    minEval = min(minEval, eval);
                    b = min(b, eval);

                    if (b <= a)
                    {
                        prune = true;
                        break;
                    }
                }
            }
            if (prune) { break;}
        }
        return minEval;
    }
}

int minmax(state s, int depth, int player)
{
    if (!(player == 1 || player == 2))
        return -1;

    int value = evaluate(s);
    if (depth == 0 || value == MIN || value == MAX)
        return value;

    int move;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (s.board[i][j] == 0) {
                move = (i + 1) * 10 + j + 1;
                break;
            }
        }
    }

    if (player == 1)
    {
        int maxEval = MIN;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (s.board[i][j] == 0)
                {
                    my_board nextState = s;
                    nextState.board[i][j] = 1;

                    int eval = minmaxrec(nextState, depth - 1, maxEval, MAX, false);
                    if (eval > maxEval)
                    {
                        move = (i + 1) * 10 + j + 1;
                        maxEval = eval;
                    }
                }
            }
        }
    }
    else
    {
        int minEval = MAX;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (s.board[i][j] == 0)
                {
                    my_board nextState = s;
                    nextState.board[i][j] = 2;

                    int eval = minmaxrec(nextState, depth - 1, MIN, minEval, true);
                    if (eval < minEval)
                    {
                        move = (i + 1) * 10 + j + 1;
                        minEval = eval;
                    }
                }
            }
        }
    }

    return move;
}
