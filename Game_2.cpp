#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include "Game_2.h"


int main() {
    cout << "Welcome to Four-in-a-Row!\n";
    cout << "The first player uses 'X', and the second player uses 'O'.\n\n";

    FourInARowBoard<char> board;

    HumanPlayer<char> player1("Player 1", 'X');
    HumanPlayer<char> player2("Player 2", 'O');

    Player<char>* players[] = {&player1, &player2};
    GameManager<char> gameManager(&board, players);

    player1.setBoard(&board);
    player2.setBoard(&board);

    gameManager.run();

    return 0;
}
