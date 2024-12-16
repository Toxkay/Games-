#pragma once
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
using namespace std;

// ------------------- Board Class -------------------
template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    Board(int r, int c) : rows(r), columns(c) {
        board = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new T[columns];
            fill(board[i], board[i] + columns, 0);
        }
    }

    virtual ~Board() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;
};

// ------------------- NumericalBoard Class -------------------
template <typename T>
class NumericalBoard : public Board<T> {
private:
    unordered_set<T> usedNumbers;

public:
    NumericalBoard() : Board<T>(3, 3) {}

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false; // Invalid move
        }
        if (usedNumbers.find(symbol) != usedNumbers.end()) {
            return false; // Symbol already used
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
        // Check rows
        for (int i = 0; i < this->rows; ++i) {
            if (check_sum_15(this->board[i][0], this->board[i][1], this->board[i][2])) {
                return true;
            }
        }
        // Check columns
        for (int j = 0; j < this->columns; ++j) {
            if (check_sum_15(this->board[0][j], this->board[1][j], this->board[2][j])) {
                return true;
            }
        }
        // Check diagonals
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

// ------------------- Player Class -------------------
template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;

public:
    Player(string n, T symbol) : name(n), symbol(symbol), boardPtr(nullptr) {}

    virtual void getmove(int& x, int& y) = 0;

    T getsymbol() { return symbol; }
    string getname() { return name; }
    void setBoard(Board<T>* b) { boardPtr = b; }
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
        x--; // Convert to 0-based indexing
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

// ------------------- GameManager Class -------------------
template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];

public:
    GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) : boardPtr(bPtr) {
        players[0] = playerPtr[0];
        players[1] = playerPtr[1];
    }

    void run() {
        int x, y;
        boardPtr->display_board();

        while (!boardPtr->game_is_over()) {
            for (int i = 0; i < 2; ++i) {
                players[i]->getmove(x, y);
                boardPtr->display_board();
                if (boardPtr->is_win()) {
                    cout << players[i]->getname() << " wins!\n";
                    return;
                }
                if (boardPtr->is_draw()) {
                    cout << "The game is a draw!\n";
                    return;
                }
            }
        }
    }
};


