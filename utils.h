#pragma once
enum TOKEN  { EMPTY, CROSS, NOUGHT };
enum WINNER { NO_WINNER, CROSS_WON, NOUGHT_WON, NOT_FINISHED_YET };
//enum RESULTS { NO_RESULTS, WIN_RESULTS, LOSE_RESULTS, NEUTRAL_RESULTS };
#define FIELD_SIZE 3
#define  INIT_TREE_SIZE 32000
struct input {
    int column_input;
    int row_input;
};
struct field_representation {
    enum TOKEN field_snapshot[FIELD_SIZE][FIELD_SIZE];
    enum WINNER result;
    int parent_array_index;
    int step_column;
    int step_row;
};