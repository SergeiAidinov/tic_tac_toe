#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern enum TOKEN get_token(int row,  int column);
extern void set_token(int row, int column, enum TOKEN token);
//extern enum TOKEN playing_field[FIELD_SIZE][FIELD_SIZE];
extern enum LINE;
extern struct turn_priority;
extern int turn;
enum CURRENT_RESULT figure_out_result(enum TOKEN field[FIELD_SIZE][FIELD_SIZE]);

const int MAX_USER_INPUT_LENGTH = FIELD_SIZE < 10 ? 2 : 3;
const int MIN_USER_INPUT_LENGTH = 2;
struct prioritized_field_representation prioritized_representation_template;

enum CURRENT_RESULT check_winner() {
    int cross_quantity = 0;
    int nought_quantity = 0;
    // check verticals
    for (int column = 0; column < FIELD_SIZE; column++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (get_token( row, column) == CROSS) cross_quantity++;
            else if (get_token(row, column) == NOUGHT) nought_quantity++;
        }
        if (cross_quantity == FIELD_SIZE) return CROSS_WON;
        if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    }
    // check horizontals
    for (int row = 0; row < FIELD_SIZE; row++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (get_token(row, column) == CROSS) cross_quantity++;
            else if (get_token(row, column) == NOUGHT) nought_quantity++;
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
        if (get_token(row, column) == CROSS) cross_quantity++;
        else if (get_token(row, column) == NOUGHT) nought_quantity++;
    }
    if (cross_quantity == FIELD_SIZE) return CROSS_WON;
    if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    if (turn == 9) return NO_WINNER;
    return NOT_FINISHED_YET;
}

struct input user_input() {
    int row_input = -1;
    int column_input = -1;
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
        row_input = (char) str[0] - 65;
        if (MAX_USER_INPUT_LENGTH == 2) {
            column_input = (char) str[1] - 48 - 1;
        } else {
            int dozen = (char) (str[1] - 48) * 10;
            int unit = (char) (str[2] - 48);
            column_input = dozen + unit - 1;
        }
        if (column_input >= FIELD_SIZE) input_is_valid = 0;
        free(str);
        if (!input_is_valid) printf("Invalid input.\n");
        if (get_token(row_input, column_input) != EMPTY) {
            input_is_valid = 0;
            printf("Cell is already engaged!\n");
        }
    } while (!input_is_valid);
    printf("Valid input.\n");
    struct input current_input = {row_input, column_input};
    return current_input;
}

struct field_representation pattern_after_playing_field() {
    struct field_representation representation;
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            representation.field_snapshot[row][column] = get_token(row,column);
        }
    }
    return representation;
}

enum CURRENT_RESULT figure_out_result(enum TOKEN field[FIELD_SIZE][FIELD_SIZE]) {
    int cross_quantity = 0;
    int nought_quantity = 0;
    // check verticals
    for (int row = 0; row < FIELD_SIZE; row++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (field[row][column] == CROSS) cross_quantity++;
            else if (field[row][column] == NOUGHT) nought_quantity++;
        }
        if (cross_quantity == FIELD_SIZE) return CROSS_WON;
        if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    }
    // check horizontals
    for (int column = 0; column < FIELD_SIZE; column++) {
        cross_quantity = 0;
        nought_quantity = 0;
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (field[row][column] == CROSS) cross_quantity++;
            else if (field[row][column] == NOUGHT) nought_quantity++;
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
    int column = 0;
    for (int row = 0; row < FIELD_SIZE; row++) {
        column = FIELD_SIZE - row - 1;
        if (field[row][column] == CROSS) cross_quantity++;
        else if (field[row][column] == NOUGHT) nought_quantity++;
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
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (current_representation_template.field_snapshot[row][column] == EMPTY) {
                possible_representation_template = current_representation_template;
                possible_representation_template.field_snapshot[row][column] = token;
                if (figure_out_result(possible_representation_template.field_snapshot) == result) {
                    struct input curr_input = {row, column};
                    return curr_input;
                }
            }
        }
    }
    struct input curr_input = {-1, -1};
    return curr_input;
}

void monkey_move(void) {
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (get_token(row, column) == EMPTY) {
                set_token(row, column, NOUGHT);
                return;
            }
        }
    }
}

void check_diagonals(void) {
    enum LINE left_upper_to_right_bottom_diagonal = VACANT;
    for (int diagonal = 0; diagonal < FIELD_SIZE; diagonal++) {
        if (get_token(diagonal, diagonal) == CROSS) {
            left_upper_to_right_bottom_diagonal = ENGAGED;
            break;
        }
    }
    if (left_upper_to_right_bottom_diagonal == VACANT) {
        for (int diagonal = 0; diagonal < FIELD_SIZE; diagonal++) {
            int new_value = prioritized_representation_template.field_snapshot[diagonal][diagonal];
            new_value++;
            prioritized_representation_template.field_snapshot[diagonal][diagonal] = new_value;
        }
    }
    // check diagonal left-bottom to right-upper
    int row = FIELD_SIZE - 1;
    enum LINE left_bottom_to_right_upper_diagonal = VACANT;
    for (int column = 0; column < FIELD_SIZE; column++) {
        row = row - column;
        if (get_token(row, column) == CROSS) {
            left_bottom_to_right_upper_diagonal = ENGAGED;
            break;
        }
    }
    if (left_bottom_to_right_upper_diagonal == VACANT) {
        row = FIELD_SIZE - 1;
        for (int column = 0; column < FIELD_SIZE; column++) {
            row = FIELD_SIZE - 1 - column;
            int new_value = prioritized_representation_template.field_snapshot[row][column];
            new_value++;
            prioritized_representation_template.field_snapshot[row][column] = new_value;
        }
    }
}

void check_horizontals() {
    enum LINE horizontal;
    for (int row = 0; row < FIELD_SIZE; row++) {
        horizontal = VACANT;
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (get_token(row, column) == CROSS) {
                horizontal = ENGAGED;
                break;
            }
        }
        if (horizontal == VACANT) {
            for (int column = 0; column < FIELD_SIZE; column++) {
                int new_value = prioritized_representation_template.field_snapshot[row][column];
                new_value++;
                prioritized_representation_template.field_snapshot[row][column] = new_value;
            }
        }
    }
}

void show_prioritized_representation() {
    printf("Prioritized representation:\n");
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            printf("%d", prioritized_representation_template.field_snapshot[column][row]);
        }
        printf("\n");
    }
}

void check_verticals(void) {
    enum LINE vertical;
    for (int column = 0; column < FIELD_SIZE; column++) {
        vertical = VACANT;
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (get_token(row, column) == CROSS) {
                vertical = ENGAGED;
                break;
            }
        }
        if (vertical == VACANT) {
            for (int row = 0; row < FIELD_SIZE; row++) {
                int new_value = prioritized_representation_template.field_snapshot[row][column];
                new_value++;
                prioritized_representation_template.field_snapshot[row][column] = new_value;
            }
        }
    }
}

void prepare_prioritized_template(void) {
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (get_token(row, column) != EMPTY)
                prioritized_representation_template.field_snapshot[row][column] = -1;
            else prioritized_representation_template.field_snapshot[row][column] = 0;
        }
    }
}

struct input prioritized_move(void) {
    printf("Prioritized move...\n");
    prepare_prioritized_template();
    check_horizontals();
    check_verticals();
    check_diagonals();
    show_prioritized_representation();
    struct turn_priority max_priority = {
        prioritized_representation_template.field_snapshot[0][0],
        0,0};
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int column = 0; column < FIELD_SIZE; column++) {
            if (prioritized_representation_template.field_snapshot[row][column] > max_priority.priority) {
                struct turn_priority new_max_priority = {prioritized_representation_template.field_snapshot[row][column],
                row, column};
                max_priority = new_max_priority;
            }
        }
    }
    set_token(max_priority.row, max_priority.column, NOUGHT);
    struct input current_input = {max_priority.row, max_priority.column};
    return current_input;
}

struct input computer_move(void) {
    struct input victorious_input = find_final_move(NOUGHT_WON, NOUGHT);
    if (victorious_input.column_input != -1 && victorious_input.row_input != -1) {
        printf("Victorious moving...\n");
        set_token(victorious_input.row_input, victorious_input.column_input, NOUGHT);
        //playing_field[victorious_input.row_input][victorious_input.column_input] = NOUGHT;
        return victorious_input;
    }
    struct input failure_input = find_final_move(CROSS_WON, CROSS);
    if (failure_input.column_input != -1 && failure_input.row_input != -1) {
        printf("Failure preventing moving...\n");
        set_token(failure_input.row_input, failure_input.column_input, NOUGHT);
        //playing_field[failure_input.column_input][failure_input.row_input] = NOUGHT;
        return failure_input;
    }
    return prioritized_move();
}
