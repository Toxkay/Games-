#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
using namespace std;

// ------------------- FourInARowBoard Class -------------------
template <typename T>
class FourInARowBoard : public Board<T> {
public:
    FourInARowBoard() {
        this->rows = 6;
        this->columns = 7;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            fill(this->board[i], this->board[i] + this->columns, ' '); 
        }
    }

    ~FourInARowBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (y < 0 || y >= this->columns || x != 0) {
            return false; 
        }
        for (int i = this->rows - 1; i >= 0; --i) {
            if (this->board[i][y] == ' ') {
                this->board[i][y] = symbol; 
                this->n_moves++;
                return true;
            }
        }
        return false; 
    }

    void display_board() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                cout << "|" << this->board[i][j];
            }
            cout << "|\n";
        }
        cout << string(this->columns * 2 + 1, '-') << endl;
        for (int j = 1; j <= this->columns; ++j) {
            cout << " " << j;
        }
        cout << endl;
    }

    bool check_four_in_a_row(T a, T b, T c, T d) {
        return a == b && b == c && c == d && a != ' ';
    }

    bool is_win() override {
        
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i][j + 1],
                                        this->board[i][j + 2], this->board[i][j + 3])) {
                    return true;
                }
            }
        }
        
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i + 1][j],
                                        this->board[i + 2][j], this->board[i + 3][j])) {
                    return true;
                }
            }
        }
        
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i + 1][j + 1],
                                        this->board[i + 2][j + 2], this->board[i + 3][j + 3])) {
                    return true;
                }
            }
        }
        
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 3; j < this->columns; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i + 1][j - 1],
                                        this->board[i + 2][j - 2], this->board[i + 3][j - 3])) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// ------------------- HumanPlayer Class -------------------
template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T symbol) : Player<T>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << " (" << this->symbol << "), enter a column (1-7): ";
        cin >> y;
        x = 0; 
        y--;   
    }
};

#endif // FOUR_IN_A_ROW
