#ifndef _MINIMAX_H_
#define _MINIMAX_H_
#define EMPTY     0
#define NPC       1
#define PLAYER    2
#define A_TIE     3
#define GAMEOVER       3
#define KEEPPLAYING    4
#define BOARDSIZE      9
#define STATE_FILE_NAME "minimax.log"

#include <stdio.h>
typedef struct stBoard{
    int mem[9];
    int minmax_value;
    int winner;

} tpBoard;

int minimax_decision(tpBoard *board, const int, const int, const int, const int);
int utility(tpBoard *);
void print_state(tpBoard *);
void save_state(tpBoard *);

#endif
