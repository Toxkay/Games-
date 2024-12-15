#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include "game_9.h"

using namespace std;

int get_pos_integer(const string& prompt) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        cin >> input;
        if (!all_of(input.begin(), input.end(), ::isdigit)) {
            cout << "Please enter a valid positive integer." << endl;
            continue;
        }
        value = stoi(input);
        if (value <= 0) {
            cout << "Please enter a valid positive integer." << endl;
        } else {
            break;
        }
    }
    return value;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    string name1 = "Player 1", name2 = "Player 2"; 

    char symbol1 = 'S', symbol2 = 'U'; 
    
    Player<char>* players[2];
    Ultimate_Board<char> board;
    int currentPlayer = 0;

    players[0] = new Ultimate_Player<char>(name1, symbol1);

    players[1] = new Ultimate_Player<char>(name2, symbol2);

    int playerScores[2] = {0, 0};
    bool game_over = false;

    while (!game_over) {
        cout << "\nCurrent board:" << endl;
        board.display_board();

        int x, y;
        cout << "Player " << (currentPlayer + 1) << " (" << players[currentPlayer]->getSymbol() << "), it's your turn." << endl;
        players[currentPlayer]->getmove(x, y);

        if (board.update_board(x, y, players[currentPlayer]->getSymbol())) {
            if (board.check_sus_sequence(players[currentPlayer]->getSymbol())) {
                cout << "Player " << (currentPlayer + 1) << " scores a point for creating an S-U-S sequence!" << endl;
                playerScores[currentPlayer]++;
            }

            if (board.is_draw()) {
                cout << "It's a draw! No more moves possible." << endl;
                game_over = true;
            }
        } else {
            cout << "Invalid move, try again!" << endl;
            continue;
        }

        currentPlayer = (currentPlayer + 1) % 2;
    }

    cout << "\nFinal board:" << endl;
    board.display_board();

    cout << "\nGame Over! Final Scores:" << endl;
    cout << "Player 1: " << playerScores[0] << " points" << endl;
    cout << "Player 2: " << playerScores[1] << " points" << endl;

    if (playerScores[0] > playerScores[1]) {
        cout << "Player 1 wins the game!" << endl;
    } else if (playerScores[1] > playerScores[0]) {
        cout << "Player 2 wins the game!" << endl;
    } else {
        cout << "The game is a tie!" << endl;
    }

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
