#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


extern void init_field();

extern void draw_playing_field();

extern struct input user_input();

extern void set_token(int column, int row, enum TOKEN token);

extern int computer_turn();

extern enum WINNER check_winner();

int turn = 1;
int *current_turn;

int main(void) {
    current_turn = &turn;
    setlocale(LC_ALL, "");
    init_field();
    /*set_token(0, 0, NOUGHT);
    set_token(1, 1, NOUGHT);
    set_token(2, 2, NOUGHT);*/
    do {
        draw_playing_field();
        if (*current_turn % 2 != 0) {
            struct input current_input = user_input();
            set_token(current_input.column_input, current_input.row_input, CROSS);
        } else {
            computer_turn();
        }
        enum WINNER winner = check_winner();
        if (winner == CROSS) {
            draw_playing_field();
            printf("You win!\n");
            break;
        }
        if (winner == NOUGHT) {
            draw_playing_field();
            printf("You lose!\n");
            break;
        }
        turn++;
    } while (1);

    return EXIT_SUCCESS;
}
