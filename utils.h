#pragma once
enum MODE {CONSOLE, GRAPHICS};
enum TOKEN  { EMPTY, CROSS, NOUGHT };
//enum WINNER { NO_WINNER, CROSS_WON, NOUGHT_WON };
enum CURRENT_RESULT { NO_WINNER, CROSS_WON, NOUGHT_WON, NOT_FINISHED_YET };
enum LINE { VACANT, ENGAGED };
#define FIELD_SIZE 3
struct input {
    int column_input;
    int row_input;
};
struct field_representation {
    enum TOKEN field_snapshot[FIELD_SIZE][FIELD_SIZE];
};
struct prioritized_field_representation {
    int field_snapshot[FIELD_SIZE][FIELD_SIZE];
};
struct turn_priority {
    int priority;
    int row;
    int column;
};