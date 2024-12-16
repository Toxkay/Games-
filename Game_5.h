#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <iostream>
#include <string>
#include <cstdlib>  
#include <ctime>    

using namespace std;

template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    Board() : rows(3), columns(3) {
        board = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new T[columns]{0};  
        }
    }

    virtual ~Board() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    virtual bool update_board(int x, int y, T symbol) {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
            return false;
        }
        board[x][y] = symbol;
        n_moves++;
        return true;
    }


    virtual void display_board() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == 0)
                    cout << "[ ]";
                else
                    cout << "[" << board[i][j] << "]";
            }
            cout << endl;
        }
        cout << endl;
    }

    
    virtual bool is_win() {
        
        for (int i = 0; i < rows; ++i) {
            if (check_sum_15(board[i][0], board[i][1], board[i][2])) return true;
        }

        for (int j = 0; j < columns; ++j) {
            if (check_sum_15(board[0][j], board[1][j], board[2][j])) return true;
        }

        if (check_sum_15(board[0][0], board[1][1], board[2][2]) ||
            check_sum_15(board[0][2], board[1][1], board[2][0])) return true;

        return false;
    }

    virtual bool is_draw() {
        return n_moves == rows * columns && !is_win();
    }

    virtual bool game_is_over() {
        return is_win() || is_draw();
    }

    bool check_sum_15(T a, T b, T c) {
        return a != 0 && b != 0 && c != 0 && (a + b + c == 15);
    }
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
    RandomPlayer(T symbol) : Player<T>(symbol) {}

    
    void getmove(int& x, int& y) override {
        srand(time(0));  
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
        cout << this->name << ", enter your number and position (row and column): ";
        cin >> x >> y;
        x--;  
        y--;  

        while (!this->boardPtr->update_board(x, y, this->getsymbol())) {
            cout << "Invalid move. Try again: ";
            cin >> x >> y;
            x--;
            y--;
        }
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

#endif 
