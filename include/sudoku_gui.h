// sudoku_gui.h
#ifndef SUDOKU_GUI_H
#define SUDOKU_GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Deklarasi variabel eksternal
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

// Struktur untuk texture font
struct FontTexture {
    SDL_Texture* texture;
    int width;
    int height;
};

// Array textures font eksternal
extern FontTexture fontTextures[18];

// Fungsi untuk mengelola textures
void initFontTextures();
void destroyFontTextures();

// Fungsi-fungsi SDL
void initSDL();
void renderGrid(int board[9][9], int selectedRow = -1, int selectedCol = -1);
void renderFont(int board[9][9], int validity[9][9]);
void destroySDL();

#endif // SUDOKU_GUI_H