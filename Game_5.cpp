#include "BoardGame_Classes.h"
using namespace std;

NumericalBoard::NumericalBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j] = 0;
        }
    }
}

void NumericalBoard::displayBoard() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j] == 0) {
                cout << ". ";
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool NumericalBoard::placeNumber(int row, int col, int number) {
    if (row < 0 || row >= size || col < 0 || col >= size || grid[row][col] != 0 || usedNumbers[number]) {
        return false;
    }

    grid[row][col] = number;
    usedNumbers[number] = true;
    return true;
}

bool NumericalBoard::checkWin() const {
    for (int i = 0; i < size; ++i) {
        if (grid[i][0] + grid[i][1] + grid[i][2] == 15 || 
            grid[0][i] + grid[1][i] + grid[2][i] == 15) { 
            return true;
        }
    }

    if (grid[0][0] + grid[1][1] + grid[2][2] == 15 || 
        grid[0][2] + grid[1][1] + grid[2][0] == 15) {
        return true;
    }

    return false;
}

NumericalGame::NumericalGame() : isPlayer1Turn(true) {}

void NumericalGame::play() {
    int row, col, number;

    while (true) {
        board.displayBoard();
        cout << "Player " << (isPlayer1Turn ? 1 : 2) << ", enter your move (row, col, number): ";
        cin >> row >> col >> number;

        if ((isPlayer1Turn && number % 2 == 0) || (!isPlayer1Turn && number % 2 != 0)) {
            cout << "Invalid number for this player. Try again.\n";
            continue;
        }

        if (!board.placeNumber(row, col, number)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        if (board.checkWin()) {
            board.displayBoard();
            cout << "Player " << (isPlayer1Turn ? 1 : 2) << " wins!\n";
            break;
        }

        isPlayer1Turn = !isPlayer1Turn;
    }
}

int main() {
    NumericalGame game;
    game.play();
    return 0;
}
