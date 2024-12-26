#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


extern void init_field();
extern void draw_playing_field();
extern struct input user_input();
extern void set_token(int column, int row, enum TOKEN token);
extern enum WINNER check_winner();

int main(void) {
    setlocale(LC_ALL, "");
    init_field();
    set_token(0, 0, NOUGHT);
    set_token(1, 1, NOUGHT);
    set_token(2, 2, NOUGHT);
    do {
        draw_playing_field();
        struct input current_input = user_input();
        set_token(current_input.column_input, current_input.row_input, CROSS);
        enum WINNER winner = check_winner();
    } while (1);
    /*set_token(1, 0, CROSS);
    set_token(1, 1, CROSS);
    set_token(1, 2, CROSS);*/

    enum WINNER winner = check_winner();
    printf("\n");
    draw_playing_field();

    return EXIT_SUCCESS;
}
