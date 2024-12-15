#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include "game_9.h"

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

    cout << "Player 1 " << name1 << " is assigned 'S'" << endl;
    cout << "Player 2 " << name2 << " is assigned 'U'" << endl;

    
    Player<char>* players[2];
    vector<vector<char>> board(3, vector<char>(3, ' ')); 
    int currentPlayer = 0; 

    if (type1 == 1)
        players[0] = new Ultimate_Player<char>(name1, 'S');
    else
        players[0] = new Random_Ultimate_Player<char>(name1, 'S');

    if (type2 == 1)
        players[1] = new Ultimate_Player<char>(name2, 'U');
    else
        players[1] = new Random_Ultimate_Player<char>(name2, 'U');

    int turns = 0;
    bool game_over = false;
    while (!game_over) {
        cout << "\nCurrent board:" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << (board[i][j] == ' ' ? '-' : board[i][j]) << " ";
            }
            cout << endl;
        }

        int x, y;
        cout << "Player " << (currentPlayer + 1) << " (" << (currentPlayer == 0 ? 'S' : 'U') << "), it's your turn." << endl;

        
        players[currentPlayer]->getmove(x, y);

        if (is_valid_move(x, y, board)) {
            board[x][y] = (currentPlayer == 0) ? 'S' : 'U'; 
            turns++;

            if (check_sus_sequence(board, (currentPlayer == 0) ? 'S' : 'U')) {
                cout << "Player " << (currentPlayer + 1) << " wins by creating a 'S-U-S' sequence!" << endl;
                game_over = true;
            }
        } else {
            cout << "Invalid move, try again!" << endl;
            continue;
        }

        if (turns == 9) {
            cout << "It's a draw!" << endl;
            game_over = true;
        }
        
        currentPlayer = (currentPlayer + 1) % 2;
    }

    
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
