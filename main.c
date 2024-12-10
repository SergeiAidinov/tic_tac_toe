#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

enum cell { CROSS, NOUGHT, EMPTY };

enum cell playing_field[3][3];
const int UPPER_LEFT_CORNER = 0x2554;
const int UPPER_RIGHT_CORNER = 0x2557;
const int BOTTOM_LEFT_CORNER = 0x255A;
const int BOTTOM_RIGHT_CORNER = 0x255D;
const int UPPER_LINE = 0x2550;
const int VERTICAL_BORDER = 0x2551;
const int T_SHAPED_CROSS = 0x2566;
const int REVERSED_T_SHAPED_CROSS = 0x2569;
const int GAP = 32;
const int LINE_LENGTH = 12;
const int MULTIPLICITY = 4;
const char CROSS_SIGN = 'X';
const char NOUGHT_SIGN = 'O';
const char EMPTY_SIGN = ' ';

void draw_upper_line();

void draw_bottom_line();

void draw_row(int row);

int main(void) {
    setlocale(LC_ALL, "");
    draw_upper_line();
    playing_field[0][1] = EMPTY;
    playing_field[0][2] = NOUGHT;
    draw_row(0);
    draw_bottom_line();
    return EXIT_SUCCESS;
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
