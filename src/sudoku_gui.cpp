// sudoku_gui.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include "../include/sudoku_gui.h"
#include "../include/sudoku_logic.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

// Array to store pre-rendered textures:
// [0-8]: Valid numbers (1-9) in black
// [9-17]: Invalid numbers (1-9) in red
FontTexture fontTextures[18];

void initFontTextures() {
    if (!font) {
        printf("Font not loaded, cannot create textures!\n");
        return;
    }
    
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color red = {255, 0, 0, 255};
    
    // Create textures for each number (1-9) in both valid and invalid states
    for (int i = 1; i <= 9; i++) {
        char numText[2];
        snprintf(numText, sizeof(numText), "%d", i);
        
        // Create valid (black) texture
        SDL_Surface* validSurface = TTF_RenderText_Blended(font, numText, black);
        if (!validSurface) {
            printf("Unable to render valid text surface for %d! TTF_Error: %s\n", i, TTF_GetError());
            continue;
        }
        
        fontTextures[i-1].texture = SDL_CreateTextureFromSurface(renderer, validSurface);
        fontTextures[i-1].width = validSurface->w;
        fontTextures[i-1].height = validSurface->h;
        
        if (!fontTextures[i-1].texture) {
            printf("Unable to create valid texture for %d! SDL_Error: %s\n", i, SDL_GetError());
        }
        
        SDL_FreeSurface(validSurface);
        
        // Create invalid (red) texture
        SDL_Surface* invalidSurface = TTF_RenderText_Solid(font, numText, red);
        if (!invalidSurface) {
            printf("Unable to render invalid text surface for %d! TTF_Error: %s\n", i, TTF_GetError());
            continue;
        }
        
        fontTextures[i+8].texture = SDL_CreateTextureFromSurface(renderer, invalidSurface);
        fontTextures[i+8].width = invalidSurface->w;
        fontTextures[i+8].height = invalidSurface->h;
        
        if (!fontTextures[i+8].texture) {
            printf("Unable to create invalid texture for %d! SDL_Error: %s\n", i, SDL_GetError());
        }
        
        SDL_FreeSurface(invalidSurface);
    }
    
    printf("Font textures initialized successfully\n");
}

void destroyFontTextures() {
    // Clean up all pre-rendered textures
    for (int i = 0; i < 18; i++) {
        if (fontTextures[i].texture) {
            SDL_DestroyTexture(fontTextures[i].texture);
            fontTextures[i].texture = nullptr;
        }
    }
}

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
    
    font = TTF_OpenFont("assets/fonts/NotoSans-Regular.ttf", 24);
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
    
    // Initialize font textures after font is loaded
    initFontTextures();
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
    // Check if textures are initialized
    if (!fontTextures[0].texture) {
        printf("Font textures not initialized, initializing now...\n");
        initFontTextures();
        if (!fontTextures[0].texture) {
            printf("Cannot render numbers without textures!\n");
            return;
        }
    }

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int num = board[row][col];
            if (num != 0) { // Skip empty cells
                int textureIndex;
                
                // Determine which texture to use:
                // Fixed numbers or valid user entries use black textures (0-8)
                // Invalid user entries use red textures (9-17)
                if (isFixed[row][col] || validity[row][col]) {
                    textureIndex = num - 1; // Valid: 0-8 for numbers 1-9
                } else {
                    textureIndex = num + 8; // Invalid: 9-17 for numbers 1-9
                }
                
                // Ensure index is valid
                if (textureIndex < 0 || textureIndex >= 18) {
                    printf("Invalid texture index: %d\n", textureIndex);
                    continue;
                }
                
                // Position the texture in the center of the cell
                SDL_Rect destRect = {
                    col * 50 + (50 - fontTextures[textureIndex].width) / 2,
                    row * 50 + (50 - fontTextures[textureIndex].height) / 2,
                    fontTextures[textureIndex].width,
                    fontTextures[textureIndex].height
                };
                
                // Render the pre-created texture
                SDL_RenderCopy(renderer, fontTextures[textureIndex].texture, NULL, &destRect);
            }
        }
    }
}

void destroySDL() {
    // First destroy font textures
    destroyFontTextures();
    
    // Then clean up SDL resources
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}