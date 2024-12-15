
#ifndef _3X3X_O_H
#define _3X3X_O_H


#include "BoardGame_Classes.h"
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

template <typename T>
class Myboard:public Board<T> {
private:
    unordered_set<string> validWords;


public:
    Myboard();
    ~Myboard();
    void load ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Player1 : public Player<T> {
public:
    Player1 (string name, T symbol);
   void getmove(int &x, int &y) ;

};

template <typename T>
void Myboard<T>:: load () {
    ifstream file("dict.txt");
    string word ;
    while (getline(file , word)) {
        validWords.insert(word);

    }

}

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y ) ;
};




#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
Myboard<T>::Myboard() {
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
Myboard<T>::~Myboard() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}
template <typename T>
bool Myboard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y < this->columns && y >= 0 && this->board[x][y]==0 ){
        this->board[x][y] = symbol;
        ++this->n_moves;
        return true;
    }
        return false;

 }



template <typename T>
void Myboard<T>::display_board() {
    for (int i = this->rows - 1; i >= 0; --i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == 1) {
                cout << "   ";
            } else if (this->board[i][j] == 0) {
                cout << "( )";
            } else {
                cout << "(" << this->board[i][j] << ")";
            }
        }
        cout << endl;
    }
    cout << endl;
}




template <typename T>
bool Myboard<T>::is_win() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        // Check row
        string row = "";
        for (int j = 0; j < 3; ++j) {
            row += this->board[i][j];
        }
        if (validWords.find(row) != validWords.end()) return true;

        // Check column
        string col = "";
        for (int j = 0; j < 3; ++j) {
            col += this->board[j][i];
        }
        if (validWords.find(col) != validWords.end()) return true;
    }

    // Check diagonals
    string diag1 = "", diag2 = "";
    for (int i = 0; i < 3; ++i) {
        diag1 += this->board[i][i]; // Top-left to bottom-right
        diag2 += this->board[i][2 - i]; // Top-right to bottom-left
    }
    if (validWords.find(diag1) != validWords.end() || validWords.find(diag2) != validWords.end()) {
        return true;
    }

    return false;
}



template <typename T>
bool Myboard<T>::is_draw(){
        if (this->n_moves == 9){
            return true ;
        }
    return false;
 }


template <typename T>
bool Myboard<T>::game_is_over(){
        return is_win() || is_draw();
 }

// ==========================================================


template <typename T>
Player1<T>::Player1(string name, T symbol) : Player<T>(name, symbol) {};

template<typename T>
void Player1<T>::getmove(int &x, int &y)
 {
    cout << "Enter your move (0 2): " << endl;
    cin >> x >> y ;
    cout << "Enter your character :";
    char s ;
    cin >> s;
    s = toupper(s);
    this->symbol = s ;
}


template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    char randomC = 'A' + (rand()%26);
    this->symbol = randomC;
}



#endif //_3X3X_O_H

