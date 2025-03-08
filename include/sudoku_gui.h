#ifndef SUDOKU_GUI_H
#define SUDOKU_GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

void initSDL();
void renderGrid(int board[9][9], int selectedRow = -1, int selectedCol = -1);
void renderFont(int board[9][9], int validity[9][9]);
void destroySDL();

#endif