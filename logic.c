#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


extern enum TOKEN get_token(int column, int row);

extern enum TOKEN current_node[FIELD_SIZE][FIELD_SIZE];
extern char EMPTY_SIGN;
extern char CROSS_SIGN;
extern char NOUGHT_SIGN;

extern int *current_turn;
const int MAX_USER_INPUT_LENGTH = FIELD_SIZE < 10 ? 2 : 3;
const int MIN_USER_INPUT_LENGTH = 2;
struct field_representation *p;
int actual_tree_size = 0;
int limit = 0;
int offset = 0;

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
            root_node.field_snapshot[column][row] = current_node[column][row];
        }
    }
    root_node.parent = NULL;
    return root_node;
};

void add_children_into_tree(/*int offset*/) {
    int head = offset;
    //for (head = offset; head < limit; head++) {
    while (1) {
        struct field_representation parent_node = p[head];
        int prospective_turn = *current_turn + 1;
        for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
            int row = i / FIELD_SIZE;
            int column = i % FIELD_SIZE;
            if (parent_node.field_snapshot[column][row] == EMPTY) {
                struct field_representation children_node;
                for (int field_snapshot_column = 0; field_snapshot_column < FIELD_SIZE; field_snapshot_column++) {
                    for (int playing_field_row = 0; playing_field_row < FIELD_SIZE; playing_field_row++) {
                        children_node.field_snapshot[field_snapshot_column][playing_field_row] = parent_node.field_snapshot[field_snapshot_column][playing_field_row];
                    }
                }
                if (prospective_turn % 2) children_node.field_snapshot[column][row] = NOUGHT;
                else children_node.field_snapshot[column][row] = CROSS;

                children_node.parent = &parent_node;
                for (int column = 0; column < FIELD_SIZE; column++) {
                    for (int row = 0; row < FIELD_SIZE; row++) {
                        if (children_node.field_snapshot[column][row] == EMPTY) printf("%c", EMPTY_SIGN);
                        else if (children_node.field_snapshot[column][row] == CROSS) printf("%c", CROSS_SIGN);
                        else if (children_node.field_snapshot[column][row] == NOUGHT) printf("%c", NOUGHT_SIGN);
                    }
                    printf("\n");
                }
                printf("\n");
                limit++;
                p[head] = children_node;
                if (check_winner(children_node.field_snapshot) == NOUGHT_WON)
                    return;
                //&children_node.parent
            }
        }
        printf("");
    }

    offset = head;
}

int computer_turn(void) {
    printf("Computer move: ");
    printf("%d\n", *current_turn);
    free(p);
    struct field_representation parent_node = create_root_node();

    p = malloc(INIT_TREE_SIZE * sizeof(struct field_representation));
    p[0] = parent_node;
    //offset = 0;
    actual_tree_size++;
    limit++;
    add_children_into_tree(/*offset*/);
    return 1;
}
