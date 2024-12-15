// Misere Tic Tac Toe Game(6)
#include "BoardGame_Classes.h"
#include "Game_6.h"
#include <bits/stdc++.h>

using namespace std;

// function to get positive integer inputs
int get_pos_integer(const string &prompt)
{
    string input;
    int value;

    while (true)
    {
        cout << prompt;
        cin >> input;
        if (!all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "Please enter a valid positive integer." << endl;
            continue;
        }
        value = stoi(input);
        if (value <= 0)
        {
            cout << "Please enter a valid positive integer." << endl;
        }
        else
        {
            break;
        }
    }
    return value;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    // player and board setup
    string name1, name2;
    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);

    // choosing player types
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n3. AI\n";
    int type1 = get_pos_integer("Enter your choice: ");
    while (type1 > 3 && type1 < 1)
    {
        cout << "Invalid choice. Choose 1 for Human or 2 for Random Computer or 3 for AI: ";
        type1 = get_pos_integer("Enter your choice: ");
    }

    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n3. AI\n";
    int type2 = get_pos_integer("Enter your choice: ");
    while (type2 > 3 && type2 < 1)
    {
        cout << "Invalid choice. Choose 1 for Human or 2 for Random Computer or 3 for AI: ";
        type2 = get_pos_integer("Enter your choice: ");
    }

    cout << name1 << " is assigned 'X'.\n";
    cout << name2 << " is assigned 'O'.\n";

    // creates players and board
    Player<char> *players[2];
    Misere_Board<char> *B = new Misere_Board<char>();
    if (type1 == 1)
        players[0] = new Misere_Player<char>(name1, 'X');
    else if (type1 == 2)
        players[0] = new Random_Misere_Player<char>(name1, 'X');
    else if (type1 == 3)
    {
        players[0] = new Misere_AI_Player<char>(name1, 'X');
        players[0]->setBoard(B);
    }
    if (type2 == 1)
        players[1] = new Misere_Player<char>(name2, 'O');
    else if (type2 == 2)
        players[1] = new Random_Misere_Player<char>(name2, 'O');
    else if (type2 == 3)
    {
        players[1] = new Misere_AI_Player<char>(name2, 'O');
        players[1]->setBoard(B);
    }
    GameManager<char> Misere(B, players);
    Misere.run();
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    system("pause");
}
