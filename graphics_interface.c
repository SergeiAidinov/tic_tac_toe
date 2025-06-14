#include <stdio.h>
#include <SDL3/SDL.h>
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
extern void draw_playing_field();
struct color_rgb background_color = {240, 220, 130};

SDL_FRect createFRect(int x, int y, int width, int height);
SDL_Renderer *renderer;
SDL_Texture *car_texture;
SDL_Texture *plane_texture;
SDL_Window *window;
extern struct input defineSquare(float x_coord, float y_coord);
extern void set_token(int column, int row, enum TOKEN token);
int handle_current_input(struct input current_input);

int draw_graphics_field() {
    printf("Hello World!\n");
    /*SDL_Window **/window = SDL_CreateWindow("Hello SDL3", TTT_GAME_WINDOW_SIZE, TTT_GAME_WINDOW_SIZE, 0);
    /*SDL_Renderer*/ renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawColor(renderer, background_color.red, background_color.green, background_color.blue, 0);
    SDL_RenderClear(renderer);
    SDL_Surface *car = SDL_LoadBMP("/home/sergei/CLionProjects/tic-tac-toe/resources/cross.bmp");
    SDL_Surface *plane = SDL_LoadBMP("/home/sergei/CLionProjects/tic-tac-toe/resources/nought.bmp");
    /*SDL_Texture **/car_texture = SDL_CreateTextureFromSurface(renderer, car);
    /*SDL_Texture **/plane_texture = SDL_CreateTextureFromSurface(renderer, plane);
    //SDL_FRect car_frect = createFRect(0, 0, SQUARE_SIZE, SQUARE_SIZE);
    //SDL_FRect plane_frect = createFRect(SQUARE_SIZE + 1, SQUARE_SIZE + 1, SQUARE_SIZE, SQUARE_SIZE);
    //SDL_RenderTexture(renderer, car_texture, NULL, &car_frect);
    //SDL_RenderTexture(renderer, plane_texture, NULL, &plane_frect);
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
                valid_input = handle_current_input(current_input);
            }
        }
    }
}

int handle_current_input(struct input current_input) {
    if (get_token(current_input.row_input, current_input.column_input) != EMPTY) {
        printf("X: %i, Y: %i engaged!!!\n",  current_input.column_input, current_input.row_input);
        return 0;
    }
    set_token(current_input.row_input, current_input.column_input, CROSS);
    SDL_FRect car_frect = createFRect(current_input.column_input * SQUARE_SIZE, current_input.row_input * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    SDL_RenderTexture(renderer, car_texture, NULL, &car_frect);
    for (float i = SQUARE_SIZE; i < TTT_GAME_WINDOW_SIZE; i+= SQUARE_SIZE) {
        SDL_RenderLine(renderer, i, 0, i, TTT_GAME_WINDOW_SIZE);
        SDL_RenderLine(renderer, 0, i, TTT_GAME_WINDOW_SIZE, i);
    }
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
    draw_playing_field();
    return 1;

}

struct input defineSquare(float y_coord, float x_coord) {
    int x = x_coord / SQUARE_SIZE;
    int y = y_coord / SQUARE_SIZE;
    struct input current_input = {y, x};
    return current_input;
}