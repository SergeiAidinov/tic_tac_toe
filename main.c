#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

extern void draw_playing_field();
extern void set_token(int column, int row, enum TOKEN token);
extern enum WINNER check_winner();


int main(void) {
    setlocale(LC_ALL, "");
    /*set_token(1, 0, CROSS);
    set_token(1, 1, CROSS);
    set_token(1, 2, CROSS);*/
    set_token(0, 0, NOUGHT);
    set_token(1, 1, NOUGHT);
    set_token(2, 2, NOUGHT);
    enum WINNER winner = check_winner();
    printf("\n");
    draw_playing_field();

    return EXIT_SUCCESS;
}
