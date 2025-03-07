#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/sudoku_gui.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 450, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("arial.ttf", 24);
}

void renderGrid(int board[9][9]) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= 9; i++) {
        SDL_RenderDrawLine(renderer, i * 50, 0, i * 50, 450);
        SDL_RenderDrawLine(renderer, 0, i * 50, 450, i * 50);
    }

    SDL_RenderPresent(renderer);
}

void destroySDL() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
