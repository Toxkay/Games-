#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
#include "Game_5.h"

using namespace std;

int main() {
    int choice;
    string playerName1, playerName2;

    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    cout << "Choose Player 1 type:\n1. Human Player\n2. Random Player\nEnter choice (1 or 2): ";
    cin >> choice;

    Player<int>* player1;
    if (choice == 1) {
        player1 = new HumanPlayer<int>(playerName1, 1);  
    } else {
        player1 = new RandomPlayer<int>(1);  
    }

    cout << "Enter Player 2's name: ";
    cin >> playerName2;
    cout << "Choose Player 2 type:\n1. Human Player\n2. Random Player\nEnter choice (1 or 2): ";
    cin >> choice;

    Player<int>* player2;
    if (choice == 1) {
        player2 = new HumanPlayer<int>(playerName2, 2);  
    } else {
        player2 = new RandomPlayer<int>(2);  
    }

    Board<int>* board = new Board<int>();

    player1->setBoard(board);
    player2->setBoard(board);

    Player<int>* players[2] = {player1, player2};
    GameManager<int> gameManager(board, players);
    gameManager.run();

    return 0;
}
