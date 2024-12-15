#include "BoardGame_Classes.h"
#include <iostream>

using namespace std;

BoardGame::BoardGame() : board(3, vector<char>(3, ' ')), player1Score(0), player2Score(0), currentPlayer('S'), totalMoves(0) {}

void BoardGame::displayBoard() const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "[" << board[i][j] << "]";
        }
        cout << endl;
    }
}

bool BoardGame::makeMove(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        totalMoves++;
        return true;
    }
    return false;
}

void BoardGame::switchPlayer() {
    currentPlayer = (currentPlayer == 'S') ? 'U' : 'S';
}

int BoardGame::checkSUS() {
    int count = 0;

    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') {
            count++;
        }
        if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') {
            count++;
        }
    }

    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
        count++;
    }
    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
        count++;
    }

    return count;
}

bool BoardGame::checkForWin() {
    int susCount = checkSUS();
    if (susCount > 0) {
        if (currentPlayer == 'S') {
            player1Score += susCount;
        } else {
            player2Score += susCount;
        }
        return true;
    }
    return totalMoves == 9;
}

int BoardGame::getPlayerScore(char player) const {
    return (player == 'S') ? player1Score : player2Score;
}

void BoardGame::play() {
    int row, col;
    while (!checkForWin()) {
        displayBoard();
        cout << "Player " << currentPlayer << "'s turn. Enter row and column (0-2): ";
        cin >> row >> col;

        if (makeMove(row, col)) {
            if (checkForWin()) {
                break;
            }
            switchPlayer();
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    displayBoard();
    cout << "Game over!\n";
    cout << "Player S score: " << player1Score << endl;
    cout << "Player U score: " << player2Score << endl;
    if (player1Score > player2Score) {
        cout << "Player S wins!" << endl;
    } else if (player2Score > player1Score) {
        cout << "Player U wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}
