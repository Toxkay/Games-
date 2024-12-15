#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    Board(int r, int c);
    virtual bool update_board(int x, T symbol);
    virtual void display_board();
    virtual bool is_win();
    virtual bool is_draw();
    virtual bool game_is_over();
};

template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;
public:
    Player(string n, T symbol);
    Player(T symbol);
    virtual void getmove(int& x);
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
};

template <typename T>
class RandomPlayer : public Player<T> {
public:
    RandomPlayer(T symbol);
    virtual void getmove(int& x);
};

template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]);
    void run();
};

#endif 
