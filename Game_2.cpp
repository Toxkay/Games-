#include "BoardGame_Classes.h"

using namespace std;

Board::Board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = '.';
        }
    }
}

void Board::displayBoard() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << "0 1 2 3 4 5 6\n"; 
}

bool Board::placeMark(int col, char mark) {
    if (col < 0 || col >= cols) return false;

    for (int i = rows - 1; i >= 0; --i) {
        if (grid[i][col] == '.') {
            grid[i][col] = mark;
            return true;
        }
    }
    return false; 
}

bool Board::checkWin(char mark) const {
    return checkHorizontal(mark) || checkVertical(mark) || checkDiagonal(mark);
}

bool Board::checkHorizontal(char mark) const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols - 3; ++j) {
            if (grid[i][j] == mark && grid[i][j + 1] == mark &&
                grid[i][j + 2] == mark && grid[i][j + 3] == mark)
                return true;
        }
    }
    return false;
}

bool Board::checkVertical(char mark) const {
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == mark && grid[i + 1][j] == mark &&
                grid[i + 2][j] == mark && grid[i + 3][j] == mark)
                return true;
        }
    }
    return false;
}

bool Board::checkDiagonal(char mark) const {
    
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < cols - 3; ++j) {
            if (grid[i][j] == mark && grid[i + 1][j + 1] == mark &&
                grid[i + 2][j + 2] == mark && grid[i + 3][j + 3] == mark)
                return true;
        }
    }
    
    for (int i = 3; i < rows; ++i) {
        for (int j = 0; j < cols - 3; ++j) {
            if (grid[i][j] == mark && grid[i - 1][j + 1] == mark &&
                grid[i - 2][j + 2] == mark && grid[i - 3][j + 3] == mark)
                return true;
        }
    }
    return false;
}


Game::Game() : currentPlayer('X') {}

void Game::play() {
    int col;
    while (true) {
        board.displayBoard();
        cout << "Player " << currentPlayer << ", enter column (0-6): ";
        cin >> col;

        if (!board.placeMark(col, currentPlayer)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        if (board.checkWin(currentPlayer)) {
            board.displayBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
    }
}

int main() {
    Game game;
    game.play();
    return 0;
}
