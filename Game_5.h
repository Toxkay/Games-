#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <unordered_set>

using namespace std;

// ------------------- NumericalBoard Class -------------------
template <typename T>
class NumericalBoard : public Board<T> {
private:
    unordered_set<T> usedNumbers;

public:
    NumericalBoard() {
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            fill(this->board[i], this->board[i] + this->columns, 0);
        }
    }

    ~NumericalBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false; 
        }
        if (usedNumbers.find(symbol) != usedNumbers.end()) {
            return false; 
        }
        this->board[x][y] = symbol;
        usedNumbers.insert(symbol);
        this->n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] == 0)
                    cout << "[ ]";
                else
                    cout << "[" << this->board[i][j] << "]";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool check_sum_15(T a, T b, T c) {
        return a != 0 && b != 0 && c != 0 && (a + b + c == 15);
    }

    bool is_win() override {
        
        for (int i = 0; i < this->rows; ++i) {
            if (check_sum_15(this->board[i][0], this->board[i][1], this->board[i][2])) {
                return true;
            }
        }
        
        for (int j = 0; j < this->columns; ++j) {
            if (check_sum_15(this->board[0][j], this->board[1][j], this->board[2][j])) {
                return true;
            }
        }
        
        if (check_sum_15(this->board[0][0], this->board[1][1], this->board[2][2]) ||
            check_sum_15(this->board[0][2], this->board[1][1], this->board[2][0])) {
            return true;
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

// ------------------- NumericalPlayer Class -------------------
template <typename T>
class NumericalPlayer : public Player<T> {
private:
    bool isOddPlayer;

public:
    NumericalPlayer(string n, T symbol, bool isOddPlayer) : Player<T>(n, symbol), isOddPlayer(isOddPlayer) {}

    void getmove(int& x, int& y) override {
        int num;
        cout << this->name << ", enter your number (";
        cout << (isOddPlayer ? "odd: 1, 3, 5, 7, 9" : "even: 2, 4, 6, 8") << ") and position (row and column): ";
        cin >> num >> x >> y;
        x--; 
        y--;
        while (!this->boardPtr->update_board(x, y, num) ||
               ((isOddPlayer && (num % 2 == 0 || num < 1 || num > 9)) ||
                (!isOddPlayer && (num % 2 != 0 || num < 1 || num > 8)))) {
            cout << "Invalid move. Try again: ";
            cin >> num >> x >> y;
            x--;
            y--;
        }
    }
};

#endif 
