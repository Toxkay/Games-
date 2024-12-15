// BoardGame_Classes.h
#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <iostream>
#include <vector>
#include <string>

class Board {
private:
    static const int rows = 6;
    static const int cols = 7;
    char grid[rows][cols];

public:
    Board();
    void displayBoard() const;
    bool placeMark(int col, char mark);
    bool checkWin(char mark) const;

private:
    bool checkHorizontal(char mark) const;
    bool checkVertical(char mark) const;
    bool checkDiagonal(char mark) const;
};

class Game {
private:
    Board board;
    char currentPlayer;

public:
    Game();
    void play();
};

#endif 
