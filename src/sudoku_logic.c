#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/sudoku_logic.h"

void initBoard(int board[9][9]) {
    memset(board, 0, sizeof(int) * 9 * 9);
}

int isValid(int board[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num) return 0;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) return 0;
        }
    }
    return 1;
}

int solveSudoku(int board[9][9], int row, int col) {
    if (row == 9) return 1;
    if (col == 9) return solveSudoku(board, row + 1, 0);
    if (board[row][col] != 0) return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1)) return 1;
            board[row][col] = 0;
        }
    }
    return 0;
}

void generateSudoku(int board[9][9], int level) {
    initBoard(board);
    srand(time(0));

    for (int i = 0; i < 9; i++) {
        int num = (rand() % 9) + 1;
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] == 0 && isValid(board, row, col, num)) {
            board[row][col] = num;
        }
    }

    solveSudoku(board, 0, 0);

    for (int i = 0; i < level; i++) {
        int row = rand() % 9;
        int col = rand() % 9;
        board[row][col] = 0;
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
