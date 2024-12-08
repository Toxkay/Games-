#include "BoardGame_Classes.h"

class ConnectFourGame {
private:
    GameBoard board;
    char currentPlayer;

public:
    ConnectFourGame() : currentPlayer('X') {}

    void playGame() {
        while (true) {
            board.displayBoard();

            
            int col;
            cout << "Player " << currentPlayer << ", choose a column (1-" << 7 << "): ";
            cin >> col;

            
            if (col < 1 || col > 7 || !board.dropPiece(col - 1, currentPlayer)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            
            if (board.checkWinner(currentPlayer)) {
                board.displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }

            
            if (board.isFull()) {
                board.displayBoard();
                cout << "The game is a draw!\n";
                break;
            }

        
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
};

int main() {
    ConnectFourGame game;
    game.playGame();
    return 0;
}
