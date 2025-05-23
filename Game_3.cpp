
//5 x 5 Tic Tac Toe Game(3)

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include "Game_3.h"

using namespace std;

// function to get positive integer inputs
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

    // player and board setup
    int n1 = 1, n2 = 2;
    string name1, name2;

    cout << "Enter Player " << n1 << " name: ";
    getline(cin >> ws, name1);

    cout << "Enter Player " << n2 << " name: ";
    getline(cin >> ws, name2);

    // choosing  player types
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
    cout <<"Player 1 "<<name1<<" is assigned  'X' "<<endl;
    cout <<"Player 2 "<<name2<<" is assigned  'O' "<<endl;

    // creates players and board
    Player<char>* players[2];
    Board5x5<char>* B = new Board5x5<char>();
    if(type1 == 1)
        players[0] = new Player5x5<char>(name1, 'X');

    else if (type1 == 2)
        players[0] = new RandomPlayer5x5<char>(name1,'X');
    if (type2 == 1)
        players[1] = new Player5x5<char>(name2, 'O');
    else if (type2 == 2)
        players[1] = new RandomPlayer5x5<char>(name2,'O');

    GameManager<char> G5x5(B, players);
    G5x5.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
