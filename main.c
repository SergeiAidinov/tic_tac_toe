#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

enum cell { X, O, EMPTY };

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

void draw_upper_line();

void draw_bottom_line();

void draw_row(int row);

int main(void) {
    setlocale(LC_ALL, "");
    draw_upper_line();
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
    for (int i = 1; i < LINE_LENGTH; i++) {
        if (i >= MULTIPLICITY & (i % MULTIPLICITY) == 0) {
            printf("%lc", VERTICAL_BORDER);
        } else if (i >= 2 & (i % 2) == 0) {
            if (playing_field[i][row] == EMPTY) printf("%c", ' ');
            else if (playing_field[i][row] == X) printf("%c", 'X');
            else if (playing_field[i][row] == O) printf("%c", 'O');
        } else {
            printf("%lc", GAP);
        }


        /*if (playing_field[i][row] == EMPTY) printf("%c", ' ');
        else if (playing_field[i][row] == X) printf("%c", 'X');
        else if (playing_field[i][row] == O) printf("%c", 'O');*/
    }
    printf("%lc", VERTICAL_BORDER);
    printf("\n");
}
