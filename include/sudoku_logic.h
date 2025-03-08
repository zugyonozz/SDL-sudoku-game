#ifndef SUDOKU_LOGIC_H
#define SUDOKU_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

extern int isFixed[9][9];
void initBoard(int board[9][9]);
int isValid(int board[9][9], int row, int col, int num);
void checkValidity(int board[9][9], int validity[9][9]);
int solveSudoku(int board[9][9], int row, int col);
void generateSudoku(int board[9][9], int level);
void printBoard(int board[9][9]);

#ifdef __cplusplus
}
#endif

#endif