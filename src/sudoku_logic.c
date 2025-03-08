// sudoku_logic.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/sudoku_logic.h"

int isFixed[9][9] = {0}; // 0 = bisa diisi user, 1 = angka tetap dari awal

void initBoard(int board[9][9]) {
    memset(board, 0, sizeof(int) * 9 * 9);
}

int isValid(int board[9][9], int row, int col, int num) {
    // Skip checking the cell itself
    int tempVal = board[row][col];
    board[row][col] = 0;
    
    // Check if number is valid in row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            board[row][col] = tempVal;
            return 0;
        }
    }
    
    // Check if number is valid in column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            board[row][col] = tempVal;
            return 0;
        }
    }
    
    // Check if number is valid in 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                board[row][col] = tempVal;
                return 0;
            }
        }
    }
    
    board[row][col] = tempVal;
    return 1;
}

void checkValidity(int board[9][9], int validity[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                validity[row][col] = 1; // Empty cells are considered valid
            } else {
                // Check if this number is valid at this position
                validity[row][col] = isValid(board, row, col, board[row][col]);
            }
        }
    }
}

int solveSudoku(int board[9][9], int row, int col) {
    if (row == 9) return 1; // If all rows are filled, puzzle is solved
    if (col == 9) return solveSudoku(board, row + 1, 0); // Move to next row
    if (board[row][col] != 0) return solveSudoku(board, row, col + 1); // Skip filled cells

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num; // Try this number
            if (solveSudoku(board, row, col + 1)) return 1; // Recursively solve rest of puzzle
            board[row][col] = 0; // If that didn't work, backtrack
        }
    }
    return 0; // No valid solution found
}

void generateSudoku(int board[9][9], int level) {
    initBoard(board);
    memset(isFixed, 0, sizeof(int) * 9 * 9); // Reset all cells as not fixed
    
    srand(time(0));

    // Place a few random numbers to start with
    for (int i = 0; i < 9; i++) {
        int num = (rand() % 9) + 1;
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] == 0 && isValid(board, row, col, num)) {
            board[row][col] = num;
        }
    }

    // Solve the board completely
    solveSudoku(board, 0, 0);
    
    // Mark all cells as fixed since this is the solved board
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            isFixed[i][j] = 1;
        }
    }

    // Remove some numbers based on difficulty level
    int cellsToRemove = 81 - (81 - level); // Adjust as needed for difficulty
    for (int i = 0; i < cellsToRemove; i++) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] != 0) {
            board[row][col] = 0;
            isFixed[row][col] = 0; // This cell can be edited by user
        } else {
            i--; // Try again if we selected an already empty cell
        }
    }
}

void printBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) printf("---------------------\n");
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) printf("| ");
            printf("%d ", board[i][j] ? board[i][j] : 0);
        }
        printf("|\n");
    }
    printf("---------------------\n");
}