#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class GameBoard {
private:
    vector<vector<char>> board;
    const int size = 3;         

public:
    GameBoard() : board(size, vector<char>(size, ' ')) {}

    void displayBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << (board[i][j] == ' ' ? '.' : board[i][j]);
                if (j < size - 1) cout << " | ";
            }
            cout << "\n";
            if (i < size - 1) cout << "---------\n";
        }
    }

    bool placeLetter(int row, int col, char letter) {
        if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != ' ') {
            return false; 
        }
        board[row][col] = letter;
        return true;
    }

    int getSize() const {
        return size;
    }

    char getCell(int row, int col) const {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            return board[row][col];
        }
        return '\0'; 
    }

    bool isFull() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }


    int countSUS(char letter) const {
        int susCount = 0;

        
        for (int i = 0; i < size; ++i) {
            
            if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') {
                ++susCount;
            }
            
            if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') {
                ++susCount;
            }
        }

        
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
            ++susCount;
        }
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
            ++susCount;
        }

        return susCount;
    }
};

#endif 
