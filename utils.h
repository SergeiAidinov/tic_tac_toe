#pragma once
enum TOKEN  { EMPTY, CROSS, NOUGHT };
//enum WINNER { NO_WINNER, CROSS_WON, NOUGHT_WON };
enum CURRENT_RESULT { NO_WINNER, CROSS_WON, NOUGHT_WON, NOT_FINISHED_YET };
#define FIELD_SIZE 3
struct input {
    int column_input;
    int row_input;
};
struct field_representation {
    enum TOKEN field_snapshot[FIELD_SIZE][FIELD_SIZE];
    enum CURRENT_RESULT result;
    int parent_array_index;
    int step_column;
    int step_row;
};