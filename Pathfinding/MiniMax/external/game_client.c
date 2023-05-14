#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include "board.h"
#define MIN -100
#define MAX 100
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
typedef struct { int board[5][5]; } state;

const int WIN_LENGTH = 28;
const int LOSE_LENGTH = 48;


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
                    state nextState = s;
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
                    state nextState = s;
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
                    state nextState = s;
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
                    state nextState = s;
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

int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[16], client_message[16];

    bool end_game;
    int player, depth, msg, move;

    if (argc != 5)
    {
        printf("Wrong number of \n");
        return -1;
    }

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0)
    {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set sort and Is the same as server-side
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Send connection request to server
    if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    // Receive the server message
    memset(server_message, '\0', sizeof(server_message));
    if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
    {
        printf("Error while receiving server's message\n");
        return -1;
    }
    printf("Server message: %s\n", server_message);

    memset(client_message, '\0', sizeof(client_message));
    strcpy(client_message, argv[3]);
    // Send the message to server
    if (send(socket_desc, client_message, strlen(client_message), 0) < 0)
    {
        printf("Unable to send message\n");
        return -1;
    }

    setBoard();
    end_game = false;
    player = atoi(argv[3]);
    depth = atoi(argv[4]);

    while (!end_game)
    {
        memset(server_message, '\0', sizeof(server_message));
        if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
        {
            printf("Error while receiving server's message\n");
            return -1;
        }
        printf("Server message: %s\n", server_message);
        msg = atoi(server_message);
        move = msg % 100;
        msg = msg / 100;
        if (move != 0)
        {
            setMove(move, 3 - player);
            printBoard();
        }
        if ((msg == 0) || (msg == 6))
        {
            printf("Your move: ");

            state s;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    s.board[i][j] = board[i][j];
                }
            }

            move = minmax(s, depth, player);
            setMove(move, player);
            printf("%d\n", move);
            printBoard();
            memset(client_message, '\0', sizeof(client_message));
            sprintf(client_message, "%d", move);
            if (send(socket_desc, client_message, strlen(client_message), 0) < 0)
            {
                printf("Unable to send message\n");
                return -1;
            }
            printf("Client message: %s\n", client_message);
        }
        else
        {
            end_game = true;
            switch (msg)
            {
            case 1:
                printf("You won.\n");
                break;
            case 2:
                printf("You lost.\n");
                break;
            case 3:
                printf("Draw.\n");
                break;
            case 4:
                printf("You won. Osonent error.\n");
                break;
            case 5:
                printf("You lost. Your error.\n");
                break;
            }
        }
    }

    // Close socket
    close(socket_desc);

    return 0;
}