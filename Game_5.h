// BoardGame_Classes.h
#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <iostream>
using namespace std;

class NumericalBoard {
private:
    static const int size = 3;
    int grid[size][size];
    bool usedNumbers[10] = {false};

public:
    NumericalBoard();
    void displayBoard() const;
    bool placeNumber(int row, int col, int number);
    bool checkWin() const;
};

class NumericalGame {
private:
    NumericalBoard board;
    bool isPlayer1Turn;

public:
    NumericalGame();
    void play();
};

#endif 
