#pragma once
enum TOKEN  { EMPTY, CROSS, NOUGHT };
enum WINNER { NO_WINNER, CROSS_WON, NOUGHT_WON };
#define FIELD_SIZE 3
struct input {
    int column_input;
    int row_input;
};