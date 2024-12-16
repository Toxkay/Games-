#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
#include "Game_5.h"

using namespace std;

int main() {
    NumericalBoard<int> board;
    NumericalPlayer<int> player1("Player 1", 0, true);  
    NumericalPlayer<int> player2("Player 2", 0, false);

    Player<int>* players[2] = {&player1, &player2};

    GameManager<int> gameManager(&board, players);

    gameManager.run();

    return 0;
}
