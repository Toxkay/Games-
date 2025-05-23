#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

#include "Game1.h"
#include "Game_3.h"
#include "Game4.h"
#include "Game_6.h"
#include "Game_7.h"
#include "Game_8.h"
#include "Game_9.h"



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


void pyramidTicTacToe() {
    
    cout << "You selected Pyramid Tic-Tac-Toe.\n";
    int choice;
    Player<char>* players[2];
    Myboard4<char>* B = new Myboard4<char>();
    string playerXName, player2Name;

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
            players[0] = new Player1<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
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
            players[1] = new Player1<char>(playerXName, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
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
}

void fourInARow() {
   
    cout << "You selected Four-in-a-row.\n";
}

void fiveByFiveTicTacToe() {
    cout << "You selected 5 x 5 Tic Tac Toe.\n";
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
}


void wordTicTacToe() {
    
    cout << "You selected Word Tic-Tac-Toe.\n";
    int choice;
    Player<char>* players[2];
    Myboard4<char>* B = new Myboard4<char>();
    string playerXName, player2Name;
    B->load();
    cout << "Welcome to FCAI Tic-tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Player4<char>(playerXName, '0');
            break;
        case 2:
            players[0] = new X_O_Random_Player4<char>('0');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
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
            players[1] = new Player4<char>(player2Name, '0');
            break;
        case 2:
            players[1] = new X_O_Random_Player4<char>('0');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }


    players[0]->setBoard(B);
    players[1]->setBoard(B);

    GameManager<char> ticgame(B, players);
    ticgame.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void numericalTicTacToe() {
    cout << "You selected Numerical Tic-Tac-Toe.\n";
}

void misereTicTacToe() {
    cout << "You selected Misere Tic Tac Toe.\n";
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

void fourbyfourTicTacToe(){
  cout << "You selected fourbyfourTicTacToe\n";
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
        return ;
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
        return ;
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

}



void ultimateTicTacToe() {
    cout << "You selected Ultimate Tic Tac Toe.\n";
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
    Ultimate_Board<char>* B = new Ultimate_Board<char>();
    if(type1 == 1)
        players[0] = new Ultimate_Player<char>(name1, 'X');

    else if (type1 == 2)
        players[0] = new Random_Ultimate_Player<char>(name1,'X');
    if (type2 == 1)
        players[1] = new Ultimate_Player<char>(name2, 'O');
    else if (type2 == 2)
        players[1] = new Random_Ultimate_Player<char>(name2,'O');

    GameManager<char> G5x5(B, players);
    G5x5.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    
}

void susGame() {
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
}

int main() {
    int choice;
    do {
        // Display the main menu
        cout << "Main Menu\n";
        cout << "---------------------------\n";
        cout << "1 - Pyramid Tic-Tac-Toe\n";
        cout << "2 - Four-in-a-row\n";
        cout << "3 - 5 x 5 Tic Tac Toe\n";
        cout << "4 - Word Tic-Tac-Toe\n";
        cout << "5 - Numerical Tic-Tac-Toe\n";
        cout << "6 - Misere Tic Tac Toe\n";
        cout << "7 - 4 x 4 Tic-Tac-Toe\n";
        cout << "8 - Ultimate Tic Tac Toe\n";
        cout << "9 - SUS\n";
        cout << "0 - Exit\n";
        cout << "---------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user choice
        switch (choice) {
            case 1:
                pyramidTicTacToe();
                break;
            case 2:
                fourInARow();
                break;
            case 3:
                fiveByFiveTicTacToe();
                break;
            case 4:
                wordTicTacToe();
                break;
            case 5:
                numericalTicTacToe();
                break;
            case 6:
                misereTicTacToe();
                break;
            case 7:
                fourbyfourTicTacToe();
                break;
            case 8:
                ultimateTicTacToe();
                break;
            case 9:
                susGame();
                break;
            case 0:
                cout << "Exiting the program\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}
