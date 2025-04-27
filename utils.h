#pragma once
enum TOKEN  { EMPTY, CROSS, NOUGHT };
enum WINNER { NO_WINNER, CROSS_WON, NOUGHT_WON };
#define FIELD_SIZE 3
#define  INIT_TREE_SIZE 4096
struct input {
    int column_input;
    int row_input;
};
struct field_representation {
    enum TOKEN field_snapshot[FIELD_SIZE][FIELD_SIZE];
    struct field_representation *parent;
};