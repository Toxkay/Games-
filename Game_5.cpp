#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
#include "Game_5.h"

using namespace std;

int main()
{
    string playerName1, playerName2;
    int choice;
    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    cout << "Choose Player 1 type:\n1. Human Player\n2. Random Player\nEnter choice (1 or 2): ";
    cin >> choice;
    Player<int> *player1;
    if (choice == 1)
    {
        player1 = new HumanPlayer<int>(playerName1, 1);
    }
    else
    {
        player1 = new Random_Player<int>(1);
    }

    cout << "Enter Player 2's name: ";
    cin >> playerName2;
    cout << "Choose Player 2 type:\n1. Human Player\n2. Random Player\nEnter choice (1 or 2): ";
    cin >> choice;
    Player<int> *player2;
    if (choice == 1)
    {
        player2 = new HumanPlayer<int>(playerName2, 2);
    }
    else
    {
        player2 = new Random_Player<int>(2);
    }

    cout << "Player 1 uses odd numbers (1, 3, 5, 7, 9)." << endl;
    cout << "Player 2 uses even numbers (2, 4, 6, 8)." << endl;

    Board<int> *board = new NumericalBoard<int>();

    player1->setBoard(board);
    player2->setBoard(board);

    Player<int> *players[2] = {player1, player2};
    GameManager<int> game(board, players);

    game.run();

    return 0;
}