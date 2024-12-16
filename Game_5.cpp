#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
#include "Game_5.h"

int main() {
    cout << "Welcome to Numerical Tic-Tac-Toe!\n";
    cout << "Player 1 uses odd numbers (1, 3, 5, 7, 9).\n";
    cout << "Player 2 uses even numbers (2, 4, 6, 8).\n\n";

    NumericalBoard<int> board;

    NumericalPlayer<int> player1("Player 1", 1, true);
    NumericalPlayer<int> player2("Player 2", 2, false);

    Player<int>* players[] = {&player1, &player2};
    GameManager<int> gameManager(&board, players);

    player1.setBoard(&board);
    player2.setBoard(&board);

    gameManager.run();

    return 0;
}
