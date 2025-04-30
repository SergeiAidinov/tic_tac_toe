#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


extern void init_field();

extern void draw_playing_field();

extern struct input user_input();
extern void computer_move(void);
extern void set_token(int column, int row, enum TOKEN token);

extern enum CURRENT_RESULT check_winner();

int turn = 1;
void gameplay() {
    do {
        system("clear");
        draw_playing_field();
        if (turn % 2 != 0) {
            struct input current_input = user_input();
            set_token(current_input.column_input, current_input.row_input, CROSS);
        } else {
            computer_move();
            //draw_playing_field();
        }
        enum CURRENT_RESULT result = check_winner();
        if (result == CROSS_WON) {
            draw_playing_field();
            printf("You win!\n");
            break;
        }
        if (result == NOUGHT_WON) {
            draw_playing_field();
            printf("You lose!\n");
            break;
        }
        if (result == NO_WINNER) {
            draw_playing_field();
            printf("Draw in the game...\n");
            break;
        }
        turn++;
    } while (1);
}