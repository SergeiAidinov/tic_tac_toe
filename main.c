#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

extern void draw_playing_field();


int main(void) {
    setlocale(LC_ALL, "");
    //playing_field[2][0] = CROSS;
    //playing_field[0][2] = NOUGHT;
    draw_playing_field();
    return EXIT_SUCCESS;
}


