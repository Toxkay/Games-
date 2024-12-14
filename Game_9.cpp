#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class SUSGame {
private:
    GameBoard board;
    int player1Score = 0;
    int player2Score = 0;

    void displayScores() const {
        cout << "Scores:\n";
        cout << "Player 1: " << player1Score << "\n";
        cout << "Player 2: " << player2Score << "\n";
    }

    bool isValidLetter(char letter) const {
        return letter == 'S' || letter == 'U';
    }

public:
    void playGame() {
        int turn = 1;
        char player1Letter, player2Letter;

        
        cout << "Player 1, choose your letter (S or U): ";
        cin >> player1Letter;
        if (!isValidLetter(player1Letter)) {
            cout << "Invalid letter. Defaulting to 'S'.\n";
            player1Letter = 'S';
        }

        player2Letter = (player1Letter == 'S') ? 'U' : 'S';
        cout << "Player 2 will use: " << player2Letter << "\n";

        while (true) {
            board.displayBoard();
            displayScores();

        
            char currentLetter = (turn % 2 == 1) ? player1Letter : player2Letter;
            cout << "Player " << ((turn % 2 == 1) ? "1" : "2") << " (" << currentLetter
                 << "), enter your move (row and column): ";

            int row, col;
            cin >> row >> col;

            
            if (!board.placeLetter(row, col, currentLetter)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            
            int newSUS = board.countSUS(currentLetter);
            if (turn % 2 == 1) {
                player1Score += newSUS;
            } else {
                player2Score += newSUS;
            }

            
            if (board.isFull()) {
                board.displayBoard();
                displayScores();
                cout << "Game over!\n";
                if (player1Score > player2Score) {
                    cout << "Player 1 wins!\n";
                } else if (player2Score > player1Score) {
                    cout << "Player 2 wins!\n";
                } else {
                    cout << "It's a draw!\n";
                }
                break;
            }

            
            ++turn;
        }
    }
};

int main() {
    SUSGame game;
    game.playGame();
    return 0;
}
