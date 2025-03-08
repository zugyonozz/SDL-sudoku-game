// sudoku_gui.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include "../include/sudoku_gui.h"
#include "../include/sudoku_logic.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    
    if (TTF_Init() < 0) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return;
    }
    
    window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 450, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    
    font = TTF_OpenFont("assets/fonts/NotoSans-Regular.ttf", 48);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        // Fallback to Arial or any system font if available
        font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 24); // Windows
        if (!font) {
            font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24); // Linux
            if (!font) {
                printf("No fallback font found!\n");
            }
        }
    }
}

void renderGrid(int board[9][9], int selectedRow, int selectedCol) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw selected cell highlight
    if (selectedRow >= 0 && selectedCol >= 0) {
        SDL_SetRenderDrawColor(renderer, 230, 230, 250, 255); // Light lavender
        SDL_Rect selectedRect = {selectedCol * 50, selectedRow * 50, 50, 50};
        SDL_RenderFillRect(renderer, &selectedRect);
    }

    // Draw grid
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Light gray for normal lines
    for (int i = 0; i <= 9; i++) {
        // Regular grid lines
        SDL_RenderDrawLine(renderer, i * 50, 0, i * 50, 450);
        SDL_RenderDrawLine(renderer, 0, i * 50, 450, i * 50);
    }
    
    // Draw thicker lines for 3x3 boxes
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for box lines
    for (int i = 0; i <= 9; i += 3) {
        // Thicker lines every 3 cells (3x3 boxes)
        for (int j = 0; j < 3; j++) {
            SDL_RenderDrawLine(renderer, i * 50 + j, 0, i * 50 + j, 450);
            SDL_RenderDrawLine(renderer, 0, i * 50 + j, 450, i * 50 + j);
        }
    }
}

void renderFont(int board[9][9], int validity[9][9]) {
    if (!font) {
        printf("Font not loaded, cannot render text!\n");
        return;
    }

    SDL_Color black = {0, 0, 0, 255};
    SDL_Color red = {255, 0, 0, 255};

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != 0) {
                char numText[2];
                snprintf(numText, sizeof(numText), "%d", board[row][col]);

                // Choose color based on whether the number is fixed or valid
                SDL_Color color;
                if (isFixed[row][col]) {
                    color = black; // Original numbers are always black
                } else {
                    color = validity[row][col] ? black : red; // User numbers: black if valid, red if invalid
                }

                SDL_Surface* textSurface = TTF_RenderText_Solid(font, numText, color);
                if (!textSurface) {
                    printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
                    continue;
                }
                
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (!textTexture) {
                    printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(textSurface);
                    continue;
                }
                
                SDL_Rect textRect = {col * 50 + 20, row * 50 + 10, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }
    }
}

void destroySDL() {
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}