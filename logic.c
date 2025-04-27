#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


extern enum TOKEN get_token(int column, int row);

extern enum TOKEN playing_field[FIELD_SIZE][FIELD_SIZE];
extern char EMPTY_SIGN;
extern char CROSS_SIGN;
extern char NOUGHT_SIGN;
extern int turn;
const int MAX_USER_INPUT_LENGTH = FIELD_SIZE < 10 ? 2 : 3;
const int MIN_USER_INPUT_LENGTH = 2;
struct field_representation *tree;
int actual_tree_size = 0;
int limit = 0;
int offset = 0;
int prospective_turn;

enum WINNER check_winner(enum TOKEN field[FIELD_SIZE][FIELD_SIZE]) {
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
        // Проверяем, что цифры укдадываются в размер поля
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

struct field_representation create_root_node(void) {
    struct field_representation root_node;
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            root_node.field_snapshot[column][row] = playing_field[column][row];
        }
    }
    root_node.parent = NULL;
    root_node.step_column = -1;
    root_node.step_row = -1;
    return root_node;
};

struct field_representation pattern_after_parent_node(struct field_representation parent_node) {
    struct field_representation children_node;
    for (int field_snapshot_column = 0; field_snapshot_column < FIELD_SIZE; field_snapshot_column++) {
        for (int field_snapshot_row = 0; field_snapshot_row < FIELD_SIZE; field_snapshot_row++) {
            children_node.field_snapshot[field_snapshot_column][field_snapshot_row] = parent_node.
                    field_snapshot[field_snapshot_column][field_snapshot_row];
        }
    }
    children_node.parent = &parent_node;
    return children_node;
}

void show_node(struct field_representation node) {
    //printf("Parent node: ");
    printf("%s %p\n", "Parent node: ", node.parent);
    //printf("Turn: ");
    int turn_to_show = prospective_turn != 0 ? prospective_turn : 1;
    printf("%s %d\n", "Turn: ", turn_to_show);
    printf("%s %d\n", "Column step: ", node.step_column);
    printf("%s %d\n", "Row step: ", node.step_row);
    for (int column = 0; column < FIELD_SIZE; column++) {
        for (int row = 0; row < FIELD_SIZE; row++) {
            if (node.field_snapshot[column][row] == EMPTY) printf("%c", EMPTY_SIGN);
            else if (node.field_snapshot[column][row] == CROSS) printf("%c", CROSS_SIGN);
            else if (node.field_snapshot[column][row] == NOUGHT) printf("%c", NOUGHT_SIGN);
        }
        printf("\n");
    }
    printf("\n");
}

enum TOKEN figure_out_current_token() {
    if (prospective_turn % 2 == 0)
        return NOUGHT;
    else return CROSS;
}

int add_all_children_into_tree(struct field_representation parent_node) {
    enum TOKEN current_token = figure_out_current_token();
    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
        int row = i % FIELD_SIZE;
        int column = i / FIELD_SIZE;
        if (parent_node.field_snapshot[column][row] == EMPTY) {
            struct field_representation children_node = pattern_after_parent_node(parent_node);
            children_node.field_snapshot[column][row] = current_token;
            children_node.parent = &parent_node;
            children_node.step_column = row;
            children_node.step_row = column;
            show_node(children_node);
            tree[limit] = children_node;
            limit++;
            if (check_winner(children_node.field_snapshot) == NOUGHT_WON)
                return 1;
        }
    }
    return 0;
}

void plant_tree(void) {
    limit = 0;
    offset = 0;
    struct field_representation root_node = create_root_node();
    tree[limit] = root_node;
    show_node(tree[limit]);
    limit++;
    prospective_turn = turn;
}

void grow_tree(/*int offset*/) {
    plant_tree();
    int is_found = add_all_children_into_tree(tree[offset]);
    offset++;
    if (is_found) return;
    while (limit - offset > 1) {
        prospective_turn++;
        int turn_limit = limit;
        for (offset; offset < turn_limit; offset++) {
            is_found = add_all_children_into_tree(tree[offset]);
            if (is_found) return;
        }
    }
}

int computer_turn(void) {
    printf("Computer move: ");
    printf("%d\n", turn);
    free(tree);
    tree = malloc(INIT_TREE_SIZE * sizeof(struct field_representation));
    grow_tree(/*offset*/);
    return 1;
}
