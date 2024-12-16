#include <iostream>
#include "BoardGame_Classes.h"
#include "Game_7.h"

using namespace std;

int main()
{
    int choice;
    Player<char> *players[2];
    Board4x4<char> *B = new Board4x4<char>();
    string player1Name, player2Name;

    cout << "Welcome to the Tic-Tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> player1Name;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Player4x4<char>(player1Name, 'X');
        break;
    case 2:
        players[0] = new RandomPlayer4x4<char>(player1Name, 'X');
        break;
    default:
        cout << "Invalid choice for Player X. Exiting the game.\n";
        return 1 ;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Player4x4<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new RandomPlayer4x4<char>(player2Name, 'O');
        break;
    default:
        cout << "Invalid choice for Player O. Exiting the game.\n";
        return 1;
    }

    players[0]->setBoard(B);
    players[1]->setBoard(B);

    GameManager<char> ticGame(B, players);
    ticGame.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }

    return 0;
}
