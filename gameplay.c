#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


extern void init_field();
extern void draw_playing_field();
extern struct input user_input();
extern void computer_move(void);
extern void set_token(int column, int row, enum TOKEN token);
extern enum CURRENT_RESULT check_winner();
enum TOKEN playing_field[FIELD_SIZE][FIELD_SIZE];
void console_turn();
int turn = 1;
void gameplay(enum MODE mode) {
    do {
        if (mode == CONSOLE) {
           console_turn();
        } else {
            printf("Graphics mode!\n");
            exit(0);
        }
    } while (1);
}

void console_turn() {
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
        exit(0);
    }
    if (result == NOUGHT_WON) {
        draw_playing_field();
        printf("You lose!\n");
       exit(0);
    }
    if (result == NO_WINNER) {
        draw_playing_field();
        printf("Draw in the game...\n");
        exit(0);
    }
    turn++;
}