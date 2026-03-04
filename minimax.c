#include <stdio.h>
#include <minimax.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int max_AB(tpBoard *A, tpBoard *B){
    if (A->minmax_value >= B->minmax_value)
        return 1;
    return 0;
}

int min_AB(tpBoard *A, tpBoard *B){
    if (A->minmax_value < B->minmax_value)
        return 1;
    return 0;
}

int minimax_decision(tpBoard *board, const int p, const int deep, const int who, const int options){
    tpBoard *boards    = NULL,
            *retState  = NULL;

    int index      = 0,
        stop       = 0,
        nextplayer = 0,
        nextState  = -1,
        bestState  = 0,
        *freepos   = NULL;

//------------------------------------------------------------------------------
// It is the same for all games that use MinMax approach
//
//------------------------------------------------------------------------------
    //Testing if board is tne leaf node - Winner or gameover
    if (utility(board) == GAMEOVER){
       return p;
    }

    boards = (tpBoard *) malloc(sizeof(tpBoard) * options);
    freepos = (int *) malloc(sizeof(int) * options);
    for (int j = 0 ; j < options; j++)
      memcpy(&boards[j], board, sizeof(tpBoard));

    index = 0;
    for (int j = 0 ; j < BOARDSIZE; j++){
      assert(index <= options);
      if (board->mem[j] == EMPTY)
        freepos[index++] = j;
    }

//------------------------------------------------------------------------------
//Players are different from game to game. In this case, there is a special
//rules for each game
//
//------------------------------------------------------------------------------
    //opening the level's the plays
    index = 0;
    while (index < options ){
      if (boards[index].mem[freepos[index]] != EMPTY)
        printf("Nop\n");
      assert(boards[index].mem[freepos[index]] == EMPTY);
      boards[index].mem[freepos[index]] = who;
      index++;
    }//while (index < 0){
//------------------------------------------------------------------------------
// It is the same for all games that use MinMax approach
//
//------------------------------------------------------------------------------
    //The next PLAYER
    if (who == NPC) nextplayer = PLAYER;
    else nextplayer = NPC;

    for (int j = 0; j < options; j++){
      nextState = minimax_decision(&boards[j], freepos[j], deep + 1, nextplayer, options - 1);

      if (j == 0)
        bestState = nextState;
      else{ //if (j > 0){
        tpBoard b1, b2;
        memcpy(&b1, board, sizeof(tpBoard));
        memcpy(&b2, board, sizeof(tpBoard));
        assert(b1.mem[bestState] == 0);
        assert(b2.mem[nextState] == 0);
        b1.mem[bestState] = nextplayer;
        b2.mem[nextState] = nextplayer;
        utility(&b1);
        utility(&b2);
        if (nextplayer == NPC){
          if (max_AB(&b2, &b1)){
            bestState = nextState;
          }
        }else{//player
          if (min_AB(&b2, &b1)){
            bestState = nextState;
          }
        }//if (who == NPC){

      }//if (j == 0)

    }
    free(freepos);
    free(boards);
    return bestState;
}


/*
 * Check if the game is in final state
 * returns:
 *         Winner (1 or 2, where 1 is a player and 2 is NPC who applies MinMax algorithm)
 *         -1 is not game over
 *         42 no winner
 */
int utility(tpBoard *board){
    int flag = 0;
    int winner = -1;
    int j = 0;
    int i = 0;
    //printf("Checking if there is a winner....\n");
    do {
        i = 0;
        flag = 0;
        winner = board->mem[i++ * 3 + j];
        if (winner > 0)
            flag = 1;
        while (i < 3){ // && (flag == 0)){
            if (board->mem[i++ * 3 + j] == winner){
                flag++;
            }

        }
        j++;
    }while ((j < 3) && (flag < 3));

    if (flag == 3){
        //return winner;
        if (winner == NPC){
            board->minmax_value = 1;
            board->winner = NPC;
        }else if (winner == PLAYER){
            board->minmax_value = -1;
            board->winner = PLAYER;
        }

        return GAMEOVER;
    }
//----------------------------------------------------------
    i = 0;
    winner = -1;
    do {
        j = 0;
        flag = 0;
        winner = board->mem[i * 3 + j++];
        if (winner > 0)
            flag = 1;
        while (j < 3){ // && (flag == 0)){
            if (board->mem[i * 3 + j++] == winner){
                flag++;
            }

        }
        i++;
    }while ((i < 3) && (flag < 3));

    if (flag == 3){
      if (winner == NPC){
          board->minmax_value = 1;
          board->winner = NPC;
      }else if (winner == PLAYER){
          board->minmax_value = -1;
          board->winner = PLAYER;
      }

      return GAMEOVER;
    }

    winner = -1;
    if ((board->mem[0] == board->mem[4]) && (board->mem[4] == board->mem[8]) && (board->mem[8] != 0)){
        winner = board->mem[0];
        if (winner == NPC){
            board->minmax_value = 1;
            board->winner = NPC;
        }else if (winner == PLAYER){
            board->minmax_value = -1;
            board->winner = PLAYER;
        }
        return GAMEOVER;
    }


    if ((board->mem[2] == board->mem[4]) && (board->mem[4] == board->mem[6]) && (board->mem[6] != 0)){
        winner = board->mem[2];
        if (winner == NPC){
            board->minmax_value = 1;
            board->winner = NPC;
        }else if (winner == PLAYER){
            board->minmax_value = -1;
            board->winner = PLAYER;
        }
        return GAMEOVER;
    }

//---------------------------------------------------
    flag = 0;
    //checking if game is over with n winner
   // printf("Checking if game is over....\n");
    for (j = 0; j < 3; j++){
        for (i = 0; i < 3; i++){
            int p = j * 3 + i;
            if (board->mem[p] == 0)
                flag++;

        }
    }
    board->minmax_value = 0;
    board->winner = 0;
    if (flag > 0)
        return KEEPPLAYING;

    board->winner = A_TIE;
    return GAMEOVER; //no winner - both lost
}

/*
 * Print the board current state
 */
void print_state(tpBoard *board){
    for (int j = 0; j < 3; j++){
        for (int i = 0; i < 3; i++){
            int p = j * 3 + i;
            printf("%d ", board->mem[p]);
        }
        printf("\n");
    }

    printf("Winner: %d - score: %d \n", board->winner, board->minmax_value);
}

/*
 * Print to file the board current state.
 * Used to save the last states
 */
void save_state (tpBoard *board){
  FILE *ptr = fopen(STATE_FILE_NAME, "a+");
  assert(ptr != NULL);
  for (int j = 0; j < 3; j++){
      for (int i = 0; i < 3; i++){
          int p = j * 3 + i;
          fprintf(ptr, "%d ", board->mem[p]);
      }
      fprintf(ptr, "\n");
  }

  fprintf(ptr, "Winner: %d - score: %d \n", board->winner, board->minmax_value);
  fprintf(ptr, "------------------------------------------------------------------------------\n");
  fclose(ptr);
}
