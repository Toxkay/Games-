#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <iostream>
#include <vector>

using namespace std;

class GameBoard {
private:
    vector<vector<int>> board;
    const int rows = 3;
    const int cols = 3;

public:
    GameBoard() : board(rows, vector<int>(cols, 0)) {}

    
    void displayBoard() const {
        for (const auto &row : board) {
            for (const auto &cell : row) {
                if (cell == 0)
                    cout << "[ ]";
                else
                    cout << "[" << cell << "]";
            }
            cout << endl;
        }
    }

    
    bool placeNumber(int row, int col, int num) {
        if (row >= 0 && row < rows && col >= 0 && col < cols && board[row][col] == 0) {
            board[row][col] = num;
            return true;
        }
        return false; 
    }


    int getCellValue(int row, int col) const {
        return board[row][col];
    }

    
    bool isFull() const {
        for (const auto &row : board) {
            for (int cell : row) {
                if (cell == 0)
                    return false;
            }
        }
        return true;
    }

    
    bool checkSum15(int a, int b, int c) const {
        return a != 0 && b != 0 && c != 0 && (a + b + c == 15);
    }


    bool checkWin() const {
        
        for (int i = 0; i < rows; ++i) {
            if (checkSum15(board[i][0], board[i][1], board[i][2]))
                return true;
        }
        
        for (int j = 0; j < cols; ++j) {
            if (checkSum15(board[0][j], board[1][j], board[2][j]))
                return true;
        }
        
        if (checkSum15(board[0][0], board[1][1], board[2][2]) ||
            checkSum15(board[0][2], board[1][1], board[2][0]))
            return true;

        return false;
    }
};

#endif 
