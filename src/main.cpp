#define SDL_MAIN_HANDLED
#include <iostream>
#include "../include/sudoku_logic.h"
#include "../include/sudoku_gui.h"
#include <SDL2/SDL.h>

using namespace std;

int main() {
    int board[9][9];
    int validity[9][9];
    int userBoard[9][9]; // To track user inputs

    generateSudoku(board, 20);
    
    // Copy the initial board to userBoard
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            userBoard[i][j] = board[i][j];
        }
    }
    
    checkValidity(userBoard, validity);

    cout << "Generated Sudoku Puzzle:\n";
    printBoard(board);

    initSDL();
    
    // Main game loop
    bool quit = false;
    SDL_Event event;
    int selectedRow = -1;
    int selectedCol = -1;
    
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                selectedCol = mouseX / 50;
                selectedRow = mouseY / 50;
                
                // Ensure selection is within bounds
                if (selectedRow >= 9 || selectedCol >= 9) {
                    selectedRow = selectedCol = -1;
                } else if (isFixed[selectedRow][selectedCol]) {
                    // Can't select fixed cells
                    selectedRow = selectedCol = -1;
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (selectedRow != -1 && selectedCol != -1 && !isFixed[selectedRow][selectedCol]) {
                    // Handle number input
                    if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_9) {
                        int num = event.key.keysym.sym - SDLK_0; // Convert keycode to number
                        userBoard[selectedRow][selectedCol] = num;
                        
                        // Check validity
                        checkValidity(userBoard, validity);
                    } else if (event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == SDLK_BACKSPACE) {
                        userBoard[selectedRow][selectedCol] = 0;
                        validity[selectedRow][selectedCol] = 1; // Empty cell is valid
                    }
                }
            }
        }
        
        // Render the board
        renderGrid(userBoard, selectedRow, selectedCol);
        renderFont(userBoard, validity);
        SDL_RenderPresent(renderer);
    }
    
    destroySDL();
    return 0;
}