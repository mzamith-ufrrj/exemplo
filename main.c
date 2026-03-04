#include <stdio.h>
#include <stdlib.h>
#include <minimax.h>
#include <string.h>


//Teste
int main (int ac, char **av){

    //int mem[] = {2, 2, 0, 1, 1, 2, 2, 1, 2};
    int mem[9];
    int next = 0  ;
    int opt  = 0;
    //int mem0[] = {1, 2, 1, 2, 1, 2, 0, 0, 0};
    printf("Before:\n");
    tpBoard board;
    mem[0] = atoi(av[1]);
    mem[1] = atoi(av[2]);
    mem[2] = atoi(av[3]);
    mem[3] = atoi(av[4]);
    mem[4] = atoi(av[5]);
    mem[5] = atoi(av[6]);
    mem[6] = atoi(av[7]);
    mem[7] = atoi(av[8]);
    mem[8] = atoi(av[9]);
    next = atoi(av[10]);
    opt  = atoi(av[11]);
    printf("Opt: %d / Next: %d\n\n\n", opt, next);
    memcpy(&board.mem, &mem, sizeof(int) * 9);
    board.minmax_value = board.winner = 0; 


    print_state(&board);
    printf("------------------------------------------\n");

    utility(&board);
    printf("After:\n");
    int pos = minimax_decision(&board, 0, 0, next, opt);
    board.mem[pos] = next;

    print_state(&board);

    return EXIT_SUCCESS;
}
