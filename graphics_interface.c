#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>
#include <string.h>
#define SQUARES_IN_LINE 3
#define SQUARE_SIZE 200
#define TTT_GAME_WINDOW_SIZE (SQUARE_SIZE * SQUARES_IN_LINE)
//extern *work_dir;
struct color_rgb {
    int red, green, blue;
};
struct input {
    int row_input;
    int column_input;
};
struct color_rgb background_color = {240, 220, 130};

SDL_FRect createFRect(int x, int y, int width, int height);

draw_graphics_field() {
    printf("Hello World!\n");
    SDL_Window *window = SDL_CreateWindow("Hello SDL3", TTT_GAME_WINDOW_SIZE, TTT_GAME_WINDOW_SIZE, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawColor(renderer, background_color.red, background_color.green, background_color.blue, 0);
    SDL_RenderClear(renderer);
    SDL_Surface *car = SDL_LoadBMP("/home/sergei/CLionProjects/tic-tac-toe/resources/cross.bmp");
    SDL_Surface *plane = SDL_LoadBMP("/home/sergei/CLionProjects/tic-tac-toe/resources/cross.bmp");
    SDL_Texture *car_texture = SDL_CreateTextureFromSurface(renderer, car);
    SDL_Texture *plane_texture = SDL_CreateTextureFromSurface(renderer, plane);
    SDL_FRect car_frect = createFRect(0, 0, SQUARE_SIZE, SQUARE_SIZE);
    SDL_FRect plane_frect = createFRect(SQUARE_SIZE + 1, SQUARE_SIZE + 1, SQUARE_SIZE, SQUARE_SIZE);
    SDL_RenderTexture(renderer, car_texture, NULL, &car_frect);
    SDL_RenderTexture(renderer, plane_texture, NULL, &plane_frect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0,SDL_ALPHA_TRANSPARENT); // Красный цвет линии
    for (float i = SQUARE_SIZE; i < TTT_GAME_WINDOW_SIZE; i+= SQUARE_SIZE) {
        SDL_RenderLine(renderer, i, 0, i, TTT_GAME_WINDOW_SIZE);
        SDL_RenderLine(renderer, 0, i, TTT_GAME_WINDOW_SIZE, i);
    }
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
    SDL_Event event;
}

SDL_FRect createFRect(int x, int y, int width, int height) {
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    return rect;
}