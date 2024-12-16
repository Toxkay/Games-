#include <iostream>
#include "BoardGame_Classes.h"
#include "Game_9.h"


using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    MyBoard9<char>* B = new MyBoard9<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Tic-tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Player9<char>(playerXName, 'S');
            break;
        case 2:
            players[0] = new Random_Player9<char>('S');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
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
            players[1] = new Player9<char>(playerXName, 'U');
            break;
        case 2:
            players[1] = new Random_Player9<char>('U');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
    }

    players[0]->setBoard(B);
    players[1]->setBoard(B);

    // Create the game manager and run the game
    GameManager<char> susgame(B, players);
    susgame.run();

    cout << playerXName << " scores : " <<B->score1 << endl;
    cout << player2Name << " scores : " <<B->score2<< endl ;

    if (B->score2 > B->score1){
        cout << player2Name << " WINS!";
    } else if (B->score2 < B->score1){
        cout << playerXName << " WINS!";
    }
    else{
        cout << "DRAW";
    }

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



