#ifndef SUDOKU_LOGIC_H
#define SUDOKU_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

void generateSudoku(int board[9][9], int level);
void printBoard(int board[9][9]);

#ifdef __cplusplus
}
#endif

#endif