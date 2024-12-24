#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


extern enum TOKEN get_token(int column, int row);

const int MAX_USER_INPUT_LENGTH = FIELD_SIZE < 10 ? 2 : 3;
const int MIN_USER_INPUT_LENGTH = 2;

enum WINNER check_winner() {
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
        if (get_token(column, column) == CROSS) cross_quantity++;
        else if (get_token(column, column) == NOUGHT) nought_quantity++;
    }
    if (cross_quantity == FIELD_SIZE) return CROSS_WON;
    if (nought_quantity == FIELD_SIZE) return NOUGHT_WON;
    return NO_WINNER;
}

struct input user_input() {
  char letter;
  //char figure;
  char * inp;
  do{
      char *str = NULL, c;
      int len = 1;
      str = (char*) malloc(sizeof(char));
      printf("input string: ");
      while((c = getchar()) != '\n') {
          str[len - 1] = c;
          len++;
          str = (char*) realloc(str, len);
      }
      if ( (len - 1) > MAX_USER_INPUT_LENGTH || len < MIN_USER_INPUT_LENGTH) {
        printf("input too big or too small\n");
      }
      if (str[0] < 65 || str[0] > 90) {
        printf("First symbol has to be a letter");
      }
      for (int i = 1; i < (len - 1); i++) {
        char figure = str[i];
        if (figure < 48 || figure > 57) {
            printf("Second and following symbols have to be figures");
        }
      }
      str[len - 1] = '\0';
      printf("%s (%d symbols)\n", str, len - 1);
      free(str);
  }while(1);

}
