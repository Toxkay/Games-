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
    Board(int rows, int columns) : rows(rows), columns(columns) {
        board = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new T[columns];
            fill(board[i], board[i] + columns, ' ');
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

// ------------------- FourInARowBoard Class -------------------
template <typename T>
class FourInARowBoard : public Board<T> {
public:
    FourInARowBoard() : Board<T>(6, 7) {}

    bool update_board(int x, int y, T symbol) override {
        if (y < 0 || y >= this->columns || x != 0) {
            return false; // Invalid move
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
    }

    bool is_win() override {
        // Check horizontal
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i][j + 1],
                                        this->board[i][j + 2], this->board[i][j + 3])) {
                    return true;
                }
            }
        }
        // Check vertical
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i + 1][j],
                                        this->board[i + 2][j], this->board[i + 3][j])) {
                    return true;
                }
            }
        }
        // Check diagonals
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (check_four_in_a_row(this->board[i][j], this->board[i + 1][j + 1],
                                        this->board[i + 2][j + 2], this->board[i + 3][j + 3])) {
                    return true;
                }
            }
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
        return this->n_moves == this->rows * this->columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_four_in_a_row(T a, T b, T c, T d) {
        return a == b && b == c && c == d && a != ' ';
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
    T getsymbol() { return symbol; }
    string getname() { return name; }
    void setBoard(Board<T>* b) { boardPtr = b; }
    virtual void getmove(int& x, int& y) = 0;
};

// ------------------- HumanPlayer Class -------------------
template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T symbol) : Player<T>(n, symbol) {}
    void getmove(int& x, int& y) override {
        cout << this->name << " (" << this->symbol << "), enter a column (1-7): ";
        cin >> y;
        x = 0; // Only column input is needed
        y--;   // Convert to 0-based indexing
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
            for (int i : {0, 1}) {
                players[i]->getmove(x, y);
                while (!boardPtr->update_board(x, y, players[i]->getsymbol())) {
                    cout << "Invalid move. Try again.\n";
                    players[i]->getmove(x, y);
                }
                boardPtr->display_board();
                if (boardPtr->is_win()) {
                    cout << players[i]->getname() << " wins!\n";
                    return;
                }
                if (boardPtr->is_draw()) {
                    cout << "It's a draw!\n";
                    return;
                }
            }
        }
    }
};


