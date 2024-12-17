#ifndef _NUMERICAL_TICTACTOE_H
#define _NUMERICAL_TICTACTOE_H
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
using namespace std;

template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    virtual bool update_board(int x, int y, T symbol) = 0; 
    virtual void display_board() = 0; 
    virtual bool is_win() = 0; 
    virtual bool is_draw() = 0; 
    virtual bool game_is_over() = 0; 
};

template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;  
public:
    Player(string n, T symbol) : name(n), symbol(symbol) {}
    Player(T symbol) : name("Computer"), symbol(symbol) {}

    virtual void getmove(int& x, int& y) = 0;  
    T getsymbol() { return symbol; }
    string getname() { return name; }
    void setBoard(Board<T>* b) { boardPtr = b; }
};

template <typename T>
class RandomPlayer : public Player<T> {
public:
    RandomPlayer(T symbol) : Player<T>(symbol) { srand(time(0)); } 

    void getmove(int& x, int& y) override {
        x = rand() % 3; 
        y = rand() % 3; 

        while (!this->boardPtr->update_board(x, y, this->getsymbol())) {
            x = rand() % 3;
            y = rand() % 3;
        }
    }
};

template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T symbol) : Player<T>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (row and column): ";
        cin >> x >> y;
        x--; 
        y--; 

        while (!this->boardPtr->update_board(x, y, this->getsymbol())) {
            cout << "Invalid move. Try again (row and column): ";
            cin >> x >> y;
            x--;
            y--;
        }
    }
};

template <typename T>
class NumericalBoard : public Board<T> {
public:
    NumericalBoard() {
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;  
            }
        }
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << (this->board[i][j] == 0 ? "." : to_string(this->board[i][j])) << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) return true;
            if (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) return true;
        }
        if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) return true;
        if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) return true;
        return false;
    }

    bool is_draw() override {
        return this->n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
        boardPtr = bPtr;
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
                    players[i]->getmove(x, y);
                }
                boardPtr->display_board();
                if (boardPtr->is_win()) {
                    cout << players[i]->getname() << " wins\n";
                    return;
                }
                if (boardPtr->is_draw()) {
                    cout << "Draw!\n";
                    return;
                }
            }
        }
    }
};

