#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>
#include <string.h>

#include "utils.h"
#define SQUARES_IN_LINE 3
#define SQUARE_SIZE 200
#define TTT_GAME_WINDOW_SIZE (SQUARE_SIZE * SQUARES_IN_LINE)
extern *work_dir;
extern enum TOKEN get_token(int column, int row);
struct color_rgb {
    int red, green, blue;
};
extern struct input;
extern int turn;
extern void draw_playing_field_at_console();
extern struct input computer_move(void);
struct color_rgb background_color = {240, 220, 130};

SDL_FRect createFRect(int x, int y, int width, int height);
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *cross_texture;
SDL_Texture *nought_texture;
SDL_Texture *horizontal_black_line_texture;
SDL_Surface *cross_surface;
SDL_Surface *nought_surface;
SDL_Surface *horizontal_black_line_surface;

extern struct input defineSquare(float x_coord, float y_coord);
extern void set_token(int column, int row, enum TOKEN token);
int handle_user_input(struct input current_input);
void graphics_user_turn();
void graphics_computer_turn();

int draw_graphics_field() {
    printf("Hello World!\n");
    window = SDL_CreateWindow("Hello SDL3", TTT_GAME_WINDOW_SIZE, TTT_GAME_WINDOW_SIZE, 0);
    renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawColor(renderer, background_color.red, background_color.green, background_color.blue, 0);
    SDL_RenderClear(renderer);
    cross_surface = IMG_Load("/home/sergei/CLionProjects/tic-tac-toe/resources/cross.png");
    nought_surface = IMG_Load("/home/sergei/CLionProjects/tic-tac-toe/resources/nought.png");
    //horizontal_black_line_surface = IMG_Load("/home/sergei/CLionProjects/tic-tac-toe/resources/horizontal-black-line.png");
    horizontal_black_line_surface = IMG_Load("/home/sergei/CLionProjects/tic-tac-toe/resources/green-paint-brush-stroke-6.png");
    cross_texture = SDL_CreateTextureFromSurface(renderer, cross_surface);
    nought_texture = SDL_CreateTextureFromSurface(renderer, nought_surface);
    horizontal_black_line_texture = SDL_CreateTextureFromSurface(renderer, horizontal_black_line_surface);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0,SDL_ALPHA_TRANSPARENT); // Красный цвет линии
    for (float i = SQUARE_SIZE; i < TTT_GAME_WINDOW_SIZE; i+= SQUARE_SIZE) {
        SDL_RenderLine(renderer, i, 0, i, TTT_GAME_WINDOW_SIZE);
        SDL_RenderLine(renderer, 0, i, TTT_GAME_WINDOW_SIZE, i);
    }
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
    return 1;
}

SDL_FRect createFRect(int x, int y, int width, int height) {
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    return rect;
}

void graphics_turn() {
    if (turn % 2 != 0) {
        graphics_user_turn();
    } else {
       graphics_computer_turn();
    }
}

void graphics_user_turn() {
    SDL_Event event;
    int valid_input = 0;
    while (!valid_input) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                float x_coord = event.button.x;
                float y_coord = event.button.y;
                struct input current_input = defineSquare(y_coord, x_coord);
                printf("X: %i, Y: %i\n",  current_input.column_input, current_input.row_input);
                printf("%s %f %f\n", "Левая кнопка мыши нажата:", x_coord, y_coord);
                valid_input = handle_user_input(current_input);
            }
        }
    }
}

int handle_user_input(struct input current_input) {
    if (get_token(current_input.row_input, current_input.column_input) != EMPTY) {
        printf("X: %i, Y: %i engaged!!!\n",  current_input.column_input, current_input.row_input);
        return 0;
    }
    set_token(current_input.row_input, current_input.column_input, CROSS);
    SDL_FRect cross_frect = createFRect(current_input.column_input * SQUARE_SIZE, current_input.row_input * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    SDL_RenderTexture(renderer, cross_texture, NULL, &cross_frect);
    for (float i = SQUARE_SIZE; i < TTT_GAME_WINDOW_SIZE; i+= SQUARE_SIZE) {
        SDL_RenderLine(renderer, i, 0, i, TTT_GAME_WINDOW_SIZE);
        SDL_RenderLine(renderer, 0, i, TTT_GAME_WINDOW_SIZE, i);
    }
    //SDL_RenderClear(renderer);
    //SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
    //draw_playing_field();
    return 1;

}

void graphics_computer_turn() {
    struct input current_input = computer_move();
    SDL_FRect nought_frect = createFRect(current_input.column_input * SQUARE_SIZE, current_input.row_input * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    SDL_RenderTexture(renderer, nought_texture, NULL, &nought_frect);
    for (float i = SQUARE_SIZE; i < TTT_GAME_WINDOW_SIZE; i+= SQUARE_SIZE) {
        SDL_RenderLine(renderer, i, 0, i, TTT_GAME_WINDOW_SIZE);
        SDL_RenderLine(renderer, 0, i, TTT_GAME_WINDOW_SIZE, i);
    }
    //SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}

struct input defineSquare(float y_coord, float x_coord) {
    int x = x_coord / SQUARE_SIZE;
    int y = y_coord / SQUARE_SIZE;
    struct input current_input = {y, x};
    return current_input;
}

void graphics_end_of_game(enum CURRENT_RESULT result) {
    SDL_FRect horizontal_black_line_frect = createFRect(100, 100, 500, 100);
    SDL_RenderTexture(renderer, horizontal_black_line_texture, NULL, &horizontal_black_line_frect);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
    printf("Graphics mode\n");
    printf("Graphics mode\n");
    /*if (result == CROSS_WON) {
        draw_playing_field_at_console();
        printf("You win!\n");
        exit(0);
    }
    if (result == NOUGHT_WON) {
        draw_playing_field_at_console();
        printf("You lose!\n");
        exit(0);
    }
    if (result == NO_WINNER) {
        draw_playing_field_at_console();
        printf("Draw in the game...\n");
        exit(0);
    }*/
}