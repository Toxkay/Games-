#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include "Game_5.h"

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

    int n1 = 1, n2 = 2;
    string name1, name2;
    cout << "Enter Player " << n1 << " name: ";
    getline(cin >> ws, name1);

    cout << "Enter Player " << n2 << " name: ";
    getline(cin >> ws, name2);

    
    int type1 = 0;
    cout << "Choose Player " << n1 << " type:\n1. Human\n2. Random Computer\n";
    type1 = get_pos_integer("Enter your choice: ");
    while (type1 != 1 && type1 != 2) {
        cout << "Enter a valid choice (1 or 2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        type1 = get_pos_integer("Enter your choice: ");
    }

    int type2 = 0;
    cout << "Choose Player " << n2 << " type:\n1. Human\n2. Random Computer\n";
    type2 = get_pos_integer("Enter your choice: ");
    while (type2 != 1 && type2 != 2) {
        cout << "Enter a valid choice (1 or 2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        type2 = get_pos_integer("Enter your choice: ");
    }

    cout << "Player 1 " << name1 << " is assigned 'Odd' numbers (1, 3, 5, 7, 9)" << endl;
    cout << "Player 2 " << name2 << " is assigned 'Even' numbers (2, 4, 6, 8)" << endl;

    
    NumericalTicTacToe<int>* game = new NumericalTicTacToe<int>();
    if (type1 == 1)
        game->set_player1(new HumanPlayer<int>(name1, 1));  
    else if (type1 == 2)
        game->set_player1(new RandomPlayer<int>(name1, 1)); 


    if (type2 == 1)
        game->set_player2(new HumanPlayer<int>(name2, 2));  
    else if (type2 == 2)
        game->set_player2(new RandomPlayer<int>(name2, 2)); 

    game->play_game();

    delete game->get_player1();
    delete game->get_player2();
    delete game;

    return 0;
}
