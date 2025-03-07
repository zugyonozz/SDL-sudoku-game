#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

enum GameState {GENERATE, SOLVE};

class Sudoku {
private:
    int board[9][9];
	int boardChall[9][9];
	int level;

    bool isValid(int row, int col, int num) {
        for (int i = 0; i < 9; i++)
            if (board[row][i] == num) return false;

        for (int i = 0; i < 9; i++)
            if (board[i][col] == num) return false;

        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i + startRow][j + startCol] == num) return false;

        return true;
    }

    bool solveSudoku(int row, int col) {
        if (row == 9) return true;
        if (col == 9) return solveSudoku(row + 1, 0);

        if (board[row][col] != 0)
            return solveSudoku(row, col + 1);

        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
				board[row][col] = num;
				if (solveSudoku(row, col + 1)) return true;
				board[row][col] = 0;
            }
        }
        return false;
    }

    void generateBoard() {
        for (int i = 0; i < 9; i++) {
            int num = (rand() % 9) + 1;
            int row = rand() % 9;
            int col = rand() % 9;
            if (board[row][col] == 0 && isValid(row, col, num)) {
                board[row][col] = num;
            }
        }

        solveSudoku(0, 0);
    }

	void copyBoard(){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				boardChall[i][j] = board[i][j];
			}
        		
		}
	}

	void setHardGenerateBoardChall(int counter = 0, int level = 0){
		if(counter == level){
			return;
		}

		for(int i = 0; i < 9; i++){
			int col = rand() % 9;
			int row = rand() % 9;
			if(boardChall[row][col] != 0){
				boardChall[row][col] = 0;
			}
		}

		setHardGenerateBoardChall(counter + 1, level);
	}

public:
	Sudoku() : level(0){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				board[i][j] = 0;
			}
		}
		srand(time(0));
	}

	void generateBoardChallange(int level){
		generateBoard();
		copyBoard();
		setHardGenerateBoardChall(0, level);
	}

    void print(GameState state) {
		if(state == SOLVE){
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << board[i][j] << "\t";
				}
				cout << endl << endl;
			}	
		}else if(state == GENERATE){
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << boardChall[i][j] << "\t";
				}
				cout << endl << endl;
			}
		}
    }
};

int main() {
    Sudoku s;
    s.generateBoardChallange(18);
    s.print(GENERATE);
	cout << "--------------------------------------------------------------------"<< endl;
    s.print(SOLVE);
    return 0;
}
