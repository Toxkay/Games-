#include "BoardGame_Classes.h"
#include <unordered_set>
#include <algorithm>

class NumericalTicTacToe {
private:
    GameBoard board;
    unordered_set<int> usedNumbers;
    vector<int> oddNumbers = {1, 3, 5, 7, 9};
    vector<int> evenNumbers = {2, 4, 6, 8};

    
    bool isValidNumber(int num, bool isPlayer1) const {
        return (isPlayer1 ? oddNumbers : evenNumbers).end() !=
                   find((isPlayer1 ? oddNumbers : evenNumbers).begin(),
                        (isPlayer1 ? oddNumbers : evenNumbers).end(),
                        num) &&
               usedNumbers.find(num) == usedNumbers.end();
    }

public:
    void playGame() {
        bool isPlayer1 = true;

        while (true) {
            board.displayBoard();

            
            int num, row, col;
            cout << "Player " << (isPlayer1 ? "1 (Odd)" : "2 (Even)")
                 << ", enter your number and position (row and column): ";
            cin >> num >> row >> col;

            
            if (!board.placeNumber(row, col, num) || !isValidNumber(num, isPlayer1)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            
            usedNumbers.insert(num);

            
            if (board.checkWin()) {
                board.displayBoard();
                cout << "Player " << (isPlayer1 ? "1 (Odd)" : "2 (Even)")
                     << " wins!\n";
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
