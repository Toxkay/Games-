
#ifndef GAME_9_h
#define GAME_9_h

#include "BoardGame_Classes.h"

template <typename T>
class MyBoard9:public Board<T> {

public:
    MyBoard9();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    int score1 = 0;
    int score2 = 0;
    static int moves;
    static bool end(){
        return moves == 9;
    }
};

template <typename T>
int MyBoard9<T>::moves = 0;

template <typename T>
class Player9 : public Player<T> {
public:
    Player9 (string name, T symbol);
    void getmove(int& x, int& y) ;



};

template <typename T>
class Random_Player9 : public RandomPlayer<T>{
public:
    Random_Player9 (T symbol);
    void getmove(int &x, int &y) ;

};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
MyBoard9<T>::MyBoard9() {
    this->rows = 3;
    this->columns = 3;

    this ->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
    }

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j]= 0 ;

        }
    }

}

template <typename T>
bool MyBoard9<T>::update_board(int x, int y, T mark) {
    if (end())
        return true;
    if (x >= 0 && x < this->rows && y < this->columns && y >= 0 && this->board[x][y]==0 ){
        this->board[x][y] = mark;
        ++this->n_moves;
        moves++;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void MyBoard9<T>::display_board() {
    if (end())
        return;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool MyBoard9<T>::is_win() {
    if(end())
        return false;
    static bool rowC[3] = {false, false, false};
    static bool colC[3] = {false, false, false};
    static bool diagC[2] = {false, false};

    for (int i = 0; i < 3; ++i) {
        string row = "";
        string col = "";
        for (int j = 0; j < 3; ++j) {
            row += this->board[i][j];
            col += this->board[j][i];
        }

        if (!rowC[i] && row == "SUS") {
            if (this->n_moves % 2 == 0) {
                score2++;
            } else {
                score1++;
            }
            rowC[i] = true;
            break;
        }

        if (!colC[i] && col == "SUS") {
            if (this->n_moves % 2 == 0) {
                score2++;
            } else {
                score1++;
            }
            colC[i] = true;
            break;
        }
    }

    string diag1 = "", diag2 = "";
    for (int i = 0; i < 3; ++i) {
        diag1 += this->board[i][i];
        diag2 += this->board[i][2 - i];
    }


    if (!diagC[0] && diag1 == "SUS") {
        if (this->n_moves % 2 == 0) {
            score2++;
        } else {
            score1++;
        }
        diagC[0] = true;
    }

    if (!diagC[1] && diag2 == "SUS") {
        if (this->n_moves % 2 == 0) {
            score2++;
        } else {
            score1++;
        }
        diagC[1] = true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool MyBoard9<T>::is_draw() {
    return false;
}




template <typename T>
bool MyBoard9<T>::game_is_over() {
    return this->n_moves == 9;
}


//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Player9<T>::Player9(string name, T symbol) : Player<T>(name, symbol) {

}

template <typename T>
void Player9<T>::getmove(int& x, int& y) {
    if (MyBoard9<T>::end())
        return;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


// Constructor for X_O_Random_Player
template <typename T>
Random_Player9<T>::Random_Player9(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Random_Player9<T>::getmove(int& x, int& y) {
    if (MyBoard9<T>::end())
        return;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}







#endif
