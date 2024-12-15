#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <string>
#include <vector>

class BoardGame {
private:
    std::vector<std::vector<char>> board;
    int player1Score;
    int player2Score;
    char currentPlayer;
    int totalMoves;

    int checkSUS();

public:
    BoardGame();
    void displayBoard() const;
    bool makeMove(int row, int col);
    bool checkForWin();
    void switchPlayer();
    int getPlayerScore(char player) const;
    void play();
};

#endif // BOARDGAME_CLASSES_H
