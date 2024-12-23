#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

extern void draw_playing_field();

extern void set_token(int column, int row, enum TOKEN token);


int main(void) {
    setlocale(LC_ALL, "");
    set_token(2, 0, CROSS);
    set_token(0, 2, NOUGHT);
    //playing_field[2][0] = CROSS;
    //playing_field[0][2] = NOUGHT;
    draw_playing_field();
    return EXIT_SUCCESS;
}
