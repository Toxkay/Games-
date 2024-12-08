//Four-in-a-row Game 2

#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <vector>
#include <iostream>

using namespace std;

class GameBoard {
private:
    const int rows = 6;
    const int cols = 7;
    vector<vector<char>> board;

public:
    
    GameBoard() : board(rows, vector<char>(cols, ' ')) {}

    void displayBoard() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "|" << board[i][j];
            }
            cout << "|\n";
        }
        cout << string(cols * 2 + 1, '-') << endl;
        for (int j = 1; j <= cols; ++j) {
            cout << " " << j;
        }
        cout << endl;
    }

    
    bool dropPiece(int col, char piece) {
        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][col] == ' ') {
                board[i][col] = piece;
                return true;
            }
        }
        return false; 
    }

    bool checkWinner(char piece) const {
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j <= cols - 4; ++j) {
                if (board[i][j] == piece && board[i][j + 1] == piece &&
                    board[i][j + 2] == piece && board[i][j + 3] == piece) {
                    return true;
                }
            }
        }
        
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == piece && board[i + 1][j] == piece &&
                    board[i + 2][j] == piece && board[i + 3][j] == piece) {
                    return true;
                }
            }
        }
        
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 0; j <= cols - 4; ++j) {
                if (board[i][j] == piece && board[i + 1][j + 1] == piece &&
                    board[i + 2][j + 2] == piece && board[i + 3][j + 3] == piece) {
                    return true;
                }
            }
        }
        
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 3; j < cols; ++j) {
                if (board[i][j] == piece && board[i + 1][j - 1] == piece &&
                    board[i + 2][j - 2] == piece && board[i + 3][j - 3] == piece) {
                    return true;
                }
            }
        }
        return false;
    }

    
    bool isFull() const {
        for (int j = 0; j < cols; ++j) {
            if (board[0][j] == ' ') {
                return false;
            }
        }
        return true;
    }
};

#endif 
