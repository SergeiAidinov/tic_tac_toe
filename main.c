#include <locale.h>
#include <stdlib.h>
extern void init_field();
extern void gameplay();

int main(void) {
    setlocale(LC_ALL, "");
    init_field();
    gameplay();
    return EXIT_SUCCESS;
}