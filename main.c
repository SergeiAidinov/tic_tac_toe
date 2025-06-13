#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

extern void init_field();

extern void gameplay(enum MODE mode);

char *work_dir;
int work_directory_length;

enum MODE mode = GRAPHICS;

// gcc main.c logic.c graphics_interface.c gameplay.c console_interface.c utils.h -lSDL3 -o ttt

int main(int argc, const char *argv[]) {
    setlocale(LC_ALL, "");
    work_dir = argv[0];
    if (argc > 1 && strcmp(argv[1], "--console") == 0) mode = CONSOLE;
    init_field();
    gameplay(mode);
    return EXIT_SUCCESS;
}
