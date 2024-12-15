#include <iostream>
#include "BoardGame_Classes.h"
#include "Game_4.h"


using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    Myboard<char>* B = new Myboard<char>();
    string playerXName, player2Name;
        B->load();
    cout << "Welcome to FCAI Tic-tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Player1<char>(playerXName, '0');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('0');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;



    switch(choice) {
        case 1:
            players[1] = new Player1<char>(player2Name, '0');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('0');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }


    players[0]->setBoard(B);
    players[1]->setBoard(B);



    GameManager<char> ticgame(B, players);
    ticgame.run();
    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



