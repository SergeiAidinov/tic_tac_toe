#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


extern enum TOKEN get_token(int column, int row);

extern enum TOKEN playing_field[FIELD_SIZE][FIELD_SIZE];

enum CURRENT_RESULT figure_out_result(enum TOKEN field[FIELD_SIZE][FIELD_SIZE]);

const int MAX_USER_INPUT_LENGTH = FIELD_SIZE < 10 ? 2 : 3;
const int MIN_USER_INPUT_LENGTH = 2;

enum CURRENT_RESULT check_winner() {
    int cross_quantity = 0;
    int nought_quantity = 0;
    // check verticals
    for (int column = 0; column < FIELD_SIZE; column++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (get_token(column, row) == CROSS) cross_quantity++;
            else if (get_token(column, row) == NOUGHT) nought_quantity++;
        }
        if (cross_quantity == FIELD_SIZE) return CROSS_WON;
        if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    }
    // check horizontals
    for (int row = 0; row < FIELD_SIZE; row++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (get_token(column, row) == CROSS) cross_quantity++;
            else if (get_token(column, row) == NOUGHT) nought_quantity++;
        }
        if (cross_quantity == FIELD_SIZE) return CROSS_WON;
        if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    }
    // check diagonal left-upper to right-bottom
    cross_quantity = 0;
    nought_quantity = 0;
    for (int diagonal = 0; diagonal < FIELD_SIZE; diagonal++) {
        if (get_token(diagonal, diagonal) == CROSS) cross_quantity++;
        else if (get_token(diagonal, diagonal) == NOUGHT) nought_quantity++;
    }
    if (cross_quantity == FIELD_SIZE) return CROSS_WON;
    if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    // check diagonal left-bottom to right-upper
    cross_quantity = 0;
    nought_quantity = 0;
    int row = 0;
    for (int column = 0; column < FIELD_SIZE; column++) {
        row = FIELD_SIZE - column - 1;
        if (get_token(column, row) == CROSS) cross_quantity++;
        else if (get_token(column, row) == NOUGHT) nought_quantity++;
    }
    if (cross_quantity == FIELD_SIZE) return CROSS_WON;
    if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    return NO_WINNER;
}

struct input user_input() {
    int column_input = -1;
    int row_input = -1;
    int input_is_valid = 1;
    do {
        input_is_valid = 1;
        char *str = NULL, c;
        int len = 1;
        str = (char *) malloc(sizeof(char));
        printf("Your move: ");
        while ((c = getchar()) != '\n') {
            str[len - 1] = c;
            len++;
            str = (char *) realloc(str, len);
        }
        if ((len - 1) > MAX_USER_INPUT_LENGTH || len < MIN_USER_INPUT_LENGTH) {
            input_is_valid = 0;
        }
        str[0] = toupper(str[0]);
        //Проверяем букву
        if ((str[0] < 65 || str[0] > 90)) {
            input_is_valid = 0;
        }
        // Проверяем, что после буквы идут цифры
        for (int i = 1; i < (len - 1); i++) {
            char figure = str[i];
            if (figure < 48 || figure > 57) {
                input_is_valid = 0;
                break;
            }
        }
        // Проверяем, что буква укладывается в размер поля
        if ((char) str[0] - 65 >= FIELD_SIZE) input_is_valid = 0;
        // Проверяем, что цифры укладываются в размер поля
        column_input = (char) str[0] - 65;
        if (MAX_USER_INPUT_LENGTH == 2) {
            row_input = (char) str[1] - 48 - 1;
        } else {
            int dozen = (char) (str[1] - 48) * 10;
            int unit = (char) (str[2] - 48);
            row_input = dozen + unit - 1;
        }
        if (row_input >= FIELD_SIZE) input_is_valid = 0;
        free(str);
        if (!input_is_valid) printf("Invalid input.\n");
        if (get_token(column_input, row_input) != EMPTY) {
            input_is_valid = 0;
            printf("Cell is already engaged!\n");
        }
    } while (!input_is_valid);
    printf("Valid input.\n");
    struct input current_input = {column_input, row_input};
    return current_input;
}

struct field_representation pattern_after_playing_field() {
    struct field_representation representation;
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            representation.field_snapshot[column][row] = playing_field[column][row];
        }
    }
    return representation;
}

enum CURRENT_RESULT figure_out_result(enum TOKEN field[FIELD_SIZE][FIELD_SIZE]) {
    int cross_quantity = 0;
    int nought_quantity = 0;
    // check verticals
    for (int column = 0; column < FIELD_SIZE; column++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (field[column][row] == CROSS) cross_quantity++;
            else if (field[column][row] == NOUGHT) nought_quantity++;
        }
        if (cross_quantity == FIELD_SIZE) return CROSS_WON;
        if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    }
    // check horizontals
    for (int row = 0; row < FIELD_SIZE; row++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (field[column][row] == CROSS) cross_quantity++;
            else if (field[column][row] == NOUGHT) nought_quantity++;
        }
        if (cross_quantity == FIELD_SIZE) return CROSS_WON;
        if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    }
    // check diagonal left-upper to right-bottom
    cross_quantity = 0;
    nought_quantity = 0;
    for (int diagonal = 0; diagonal < FIELD_SIZE; diagonal++) {
        if (field[diagonal][diagonal] == CROSS) cross_quantity++;
        else if (field[diagonal][diagonal] == NOUGHT) nought_quantity++;
    }
    if (cross_quantity == FIELD_SIZE) return CROSS_WON;
    if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    // check diagonal left-bottom to right-upper
    cross_quantity = 0;
    nought_quantity = 0;
    int row = 0;
    for (int column = 0; column < FIELD_SIZE; column++) {
        row = FIELD_SIZE - column - 1;
        if (field[column][row] == CROSS) cross_quantity++;
        else if (field[column][row] == NOUGHT) nought_quantity++;
    }
    if (cross_quantity == FIELD_SIZE) return CROSS_WON;
    if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (field[row][column] == EMPTY) return NOT_FINISHED_YET;
        }
    }
    return NO_WINNER;
}

struct input find_final_move(enum CURRENT_RESULT result, enum TOKEN token) {
    struct field_representation current_representation_template = pattern_after_playing_field();
    struct field_representation possible_representation_template;
    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
        int row = i % FIELD_SIZE;
        int column = i / FIELD_SIZE;
            if (possible_representation_template.field_snapshot[column][row] == EMPTY) {
                possible_representation_template = current_representation_template;
                possible_representation_template.field_snapshot[column][row] = token;
                if (figure_out_result(possible_representation_template.field_snapshot) == result) {
                    struct input curr_input = {column, row};
                    return curr_input;
                }
            }
        }
    struct input curr_input = {-1, -1};
    return curr_input;
}

void monkey_move(void) {
    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
        int row = i % FIELD_SIZE;
        int column = i / FIELD_SIZE;
        if (playing_field[column][row] == EMPTY) {
            playing_field[column][row] = NOUGHT;
            break;
        }
    }
}

void computer_move(void) {
    struct input victorious_input = find_final_move(NOUGHT_WON, NOUGHT);
    if (victorious_input.column_input != -1 && victorious_input.row_input != -1) {
        playing_field[victorious_input.column_input][victorious_input.row_input] = NOUGHT;
        return;
    }
    struct input failure_input = find_final_move(CROSS_WON, CROSS);
    if (failure_input.column_input != -1 && failure_input.row_input != -1) {
        playing_field[failure_input.column_input][failure_input.row_input] = NOUGHT;
        return;
    }
    monkey_move();
}
