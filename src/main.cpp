#define SDL_MAIN_HANDLED
#include <iostream>
#include "../include/sudoku_logic.h"
#include "../include/sudoku_gui.h"
#include <SDL2/SDL.h>
using namespace std;

int main() {
    int board[9][9];
    generateSudoku(board, 20);
    
    cout << "Generated Sudoku Puzzle:\n";
    printBoard(board);

    initSDL();
    renderGrid(board);
    
    SDL_Delay(5000);
    destroySDL();
    
    return 0;
}
