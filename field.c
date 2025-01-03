#include <stdio.h>
#include "utils.h"

const int UPPER_LEFT_CORNER = 0x2554;
const int UPPER_RIGHT_CORNER = 0x2557;
const int BOTTOM_LEFT_CORNER = 0x255A;
const int BOTTOM_RIGHT_CORNER = 0x255D;
const int UPPER_LINE = 0x2550;
const int VERTICAL_BORDER = 0x2551;
const int T_SHAPED_CROSS = 0x2566;
const int REVERSED_T_SHAPED_CROSS = 0x2569;
const int CROSS_LINES = 0x256C;
const int MIDDLE_LINE = 0x2550;
const int LEFT_JOINT = 0x2560;
const int RIGHT_JOINT = 0x2563;
const int GAP = 32;
const int LINE_LENGTH = FIELD_SIZE * 4;
const int MULTIPLICITY = 4;
const char CROSS_SIGN = 'X';
const char NOUGHT_SIGN = 'O';
const char EMPTY_SIGN = ' ';

enum TOKEN playing_field[FIELD_SIZE][FIELD_SIZE];

void draw_upper_line();

void draw_bottom_line();

void draw_middle_line();

void draw_row(int row);

void init_field() {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            playing_field[i][j] = EMPTY;
        }
    }
}

void set_token(int column, int row, enum TOKEN token) {
    playing_field[row][column] = token;
}

enum TOKEN get_token(int column, int row) {
    return playing_field[row][column];
}

void draw_playing_field() {
    draw_upper_line();
    for (int i = 0; i < FIELD_SIZE; i++) {
        draw_row(i);
        if (i < FIELD_SIZE - 1) draw_middle_line();
        else draw_bottom_line();
    }
}

void draw_upper_line() {
    printf("%lc", UPPER_LEFT_CORNER);
    for (int i = 1; i < LINE_LENGTH; i++) {
        if (i >= MULTIPLICITY & (i % MULTIPLICITY) == 0) {
            printf("%lc", T_SHAPED_CROSS);
        } else printf("%lc", UPPER_LINE);
    }
    printf("%lc", UPPER_RIGHT_CORNER);
    printf("\n");
}

void draw_bottom_line() {
    printf("%lc", BOTTOM_LEFT_CORNER);
    for (int i = 1; i < LINE_LENGTH; i++) {
        if (i >= MULTIPLICITY & (i % MULTIPLICITY) == 0) {
            printf("%lc", REVERSED_T_SHAPED_CROSS);
        } else printf("%lc", UPPER_LINE);
    }
    printf("%lc", BOTTOM_RIGHT_CORNER);
    printf("\n");
}

void draw_row(int row) {
    printf("%lc", VERTICAL_BORDER);
    int cell_order = 0;
    for (int i = 1; i < LINE_LENGTH; i++) {
        if (i >= MULTIPLICITY & (i % MULTIPLICITY) == 0) {
            printf("%lc", VERTICAL_BORDER);
        } else if (i >= 2 & (i % 2) == 0) {
            if (playing_field[row][cell_order] == EMPTY) printf("%c", EMPTY_SIGN);
            else if (playing_field[row][cell_order] == CROSS) printf("%c", CROSS_SIGN);
            else if (playing_field[row][cell_order] == NOUGHT) printf("%c", NOUGHT_SIGN);
            cell_order++;
        } else {
            printf("%lc", GAP);
        }
    }
    printf("%lc", VERTICAL_BORDER);
    printf("\n");
}

void draw_middle_line() {
    printf("%lc", LEFT_JOINT);
    for (int i = 1; i < LINE_LENGTH; i++) {
        if (i >= MULTIPLICITY & (i % MULTIPLICITY) == 0) {
            printf("%lc", CROSS_LINES);
        } else printf("%lc", MIDDLE_LINE);
    }
    printf("%lc", RIGHT_JOINT);
    printf("\n");
}


