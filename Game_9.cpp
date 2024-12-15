#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include "game_9.h"

using namespace std;

int main() {
    srand(time(0));  
    
    SUS_Board<char> board;
    SUS_Player_1<char> player1("SUS Player 1", 'S');
    SUS_Player_2<char> player2("SUS Player 2", 'U');
    
    Player<char>* players[2] = {&player1, &player2};
    
    int x, y;
    bool gameOver = false;
    int turn = 0;  
    int playerScores[2] = {0, 0};  
    
    while (!gameOver) {
        board.display_board();  
        players[turn]->getmove(x, y);
        if (board.update_board(x, y, players[turn]->getsymbol())) {
            
            if (board.is_win()) {
                playerScores[turn]++;
                cout << (turn == 0 ? "SUS Player 1" : "SUS Player 2") << " creates an 'S-U-S' sequence and scores a point!" << endl;
            }
            
            
            if (board.game_is_over()) {
                gameOver = true;
            }
            
        
            turn = (turn + 1) % 2;  
        } else {
            cout << "Invalid move. Please try again." << endl;
        }
    }


    board.display_board();
    cout << "\nGame Over!" << endl;
    cout << "SUS Player 1 score: " << playerScores[0] << endl;
    cout << "SUS Player 2 score: " << playerScores[1] << endl;

    if (playerScores[0] > playerScores[1]) {
        cout << "SUS Player 1 wins!" << endl;
    } else if (playerScores[1] > playerScores[0]) {
        cout << "SUS Player 2 wins!" << endl;
    } else {
        cout << "The game is a draw!" << endl;
    }

    return 0;
}
