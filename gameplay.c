#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"


extern void init_field();

extern void draw_playing_field();

extern struct input user_input();

extern void computer_move(void);

extern void set_token(int column, int row, enum TOKEN token);

extern enum CURRENT_RESULT check_winner();

extern draw_graphics_field();

extern *work_dir;
extern work_directory_length;

enum TOKEN playing_field[FIELD_SIZE][FIELD_SIZE];

void console_turn();

void graphics_turn();

int turn = 1;
int field_is_drown = 0;

void gameplay(enum MODE mode) {

    do {
        if (mode == CONSOLE) {
            console_turn();
        } else {
            if (!field_is_drown) {
                field_is_drown = draw_graphics_field();
            }

            graphics_turn();
        }
    } while (1);
}

void init_field() {
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int column = 0; column < FIELD_SIZE; column++) {
            playing_field[row][column] = EMPTY;
        }
    }
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


