#ifndef GAME1_H
#define GAME1_H


#include "BoardGame_Classes.h"


template <typename T>
class Myboard: public Board<T> {
public:
    Myboard();
    ~Myboard();
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
    void getmove(int& x, int& y) ;

};
template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};




#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
Myboard<T>::Myboard() {
    this->rows = 3;
    this->columns = 5;

    this ->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
    }

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if ((i == 1 && (j == 0 || j == 4) )||(i == 2 && (j == 0 || j == 1 || j == 3 || j ==4 ))){
                this->board[i][j]= 1;
            }
            else{
                this->board[i][j]= 0 ;
            }
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
        if (this->board[0][0]!=0 && (this->board[0][0] == this->board[0][1] && this->board[0][1] == this->board[0][2])) {
            return true;
        }
        if (this->board[0][1]!=0 &&( this->board[0][1] == this->board[0][2] && this->board[0][2] == this->board[0][3])) {
            return true;
        }

        if (this->board[0][2]!= 0 && (this->board[0][2] == this->board[0][3] && this->board[0][3] == this->board[0][4])) {
            return true;
        }
        if (this->board[1][1]!= 0 && (this->board[1][1] == this->board[1][2] &&this->board[1][2] == this->board[1][3]) ) {
            return true;
        }
        if (this->board[0][2]!=0 && (this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2][2])) {
            return true;
        }
        if (this->board[0][0]!= 0 && (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])) {
            return true;
        }
        if (this->board[0][4]!= 0 &&( this->board[0][4] == this->board[1][3] && this->board[1][3] == this->board[2][2])) {
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


template <typename T>
Player1<T>::Player1(string name, T symbol) : Player<T>(name, symbol) {};

template <typename T>
void Player1<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
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
}
#endif //_3X3X_O_H

