#include "BoardGame_Classes.h"
#include <unordered_set>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class NumericalTicTacToe {
private:
    GameBoard board;
    unordered_set<int> usedNumbers;
    unordered_set<int> oddNumbers = {1, 3, 5, 7, 9};
    unordered_set<int> evenNumbers = {2, 4, 6, 8};

    bool isValidNumber(int num, bool isPlayer1) const {
        const auto& validNumbers = isPlayer1 ? oddNumbers : evenNumbers;
        return validNumbers.count(num) && !usedNumbers.count(num);
    }

    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < board.getSize() && col >= 0 && col < board.getSize();
    }

    
    bool getPlayerMove(int& num, int& row, int& col, bool isPlayer1) {
        cout << "Player " << (isPlayer1 ? "1 (Odd)" : "2 (Even)")
             << ", enter your number and position (row and column): ";
        cin >> num >> row >> col;

        if (!isValidPosition(row, col)) {
            cout << "Invalid position. Please choose a valid row and column.\n";
            return false;
        }

        if (!isValidNumber(num, isPlayer1)) {
            cout << "Invalid number. Please choose a valid " 
                 << (isPlayer1 ? "odd" : "even") << " number that hasn't been used.\n";
            return false;
        }

        if (!board.isCellEmpty(row, col)) {  
            cout << "The cell is already occupied. Try again.\n";
            return false;
        }

        return true;
    }

public:
    void playGame() {
        bool isPlayer1 = true;

        while (true) {
            board.displayBoard();

            int num, row, col;
            if (!getPlayerMove(num, row, col, isPlayer1)) {
                continue;
            }

            
            board.placeNumber(row, col, num);
            usedNumbers.insert(num);

            if (board.checkWin()) {
                board.displayBoard();
                cout << "Player " << (isPlayer1 ? "1 (Odd)" : "2 (Even)") << " wins!\n";
                break;
            }
            
            if (board.isFull()) {
                board.displayBoard();
                cout << "The game is a draw!\n";
                break;
            }

            
            isPlayer1 = !isPlayer1;
        }
    }
};

int main() {
    NumericalTicTacToe game;
    game.playGame();
    return 0;
}
