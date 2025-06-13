#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

extern void init_field();

extern void gameplay();

enum MODE mode = GRAPHICS;

int main(int argc, const char *argv[]) {
    setlocale(LC_ALL, "");
    char *work_dir = argv[0];
    if (argc > 1 && strcmp(argv[1], "--console") == 0) mode = CONSOLE;
    init_field();
    gameplay(mode);
    return EXIT_SUCCESS;
}
