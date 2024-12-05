

//Misere Tic Tac Toe Game(6)

#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;
bool Over = false;

template <typename T>
class Misere_Board : public Board<T>
{
private:
 
    bool is_valid_move(short x, short y)
    {
        if ((x >= 0 && x <= 2) && (y >= 0 && y <= 2))
        {
            if (this->board[x][y] == 0)
                return true;
        }
        return false;
    }

    void checkLOSE()
    {
        if ((this->board[0][0] == this->board[0][1]) && (this->board[0][0] == this->board[0][2]) && (this->board[0][0] != 0) ||
            (this->board[1][0] == this->board[1][1]) && (this->board[1][0] == this->board[1][2]) && (this->board[1][0] != 0) ||
            (this->board[2][0] == this->board[2][1]) && (this->board[2][0] == this->board[2][2]) && (this->board[2][0] != 0) ||
            (this->board[0][0] == this->board[1][0]) && (this->board[0][0] == this->board[2][0]) && (this->board[0][0] != 0) ||
            (this->board[0][1] == this->board[1][1]) && (this->board[0][1] == this->board[2][1]) && (this->board[0][1] != 0) ||
            (this->board[0][2] == this->board[1][2]) && (this->board[0][2] == this->board[2][2]) && (this->board[0][2] != 0) ||
            (this->board[0][0] == this->board[1][1]) && (this->board[0][0] == this->board[2][2]) && (this->board[0][0] != 0) ||
            (this->board[0][2] == this->board[1][1]) && (this->board[0][2] == this->board[2][0]) && (this->board[0][2] != 0))
            Over = true;
    }
  

public:
    Misere_Board()
    {
        this->rows = this->columns = 3;
        this->board = new char *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++)
                this->board[i][j] = 0;
        }
        this->n_moves = 0;
    }
 
    void display_board()
    {
        if (Over)
            return;
        for (int i = 0; i < this->rows; i++)
        {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++)
            {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-------------------------------";
        }
        cout << endl;
    }
 
    bool update_board(int x, int y, char symbol)
    {
        if (Over)
            return true;
        if (!is_valid_move(x, y))
            return false;
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }

    bool is_win()
    {
        if (Over)
            return true;
        checkLOSE();
        return false;
    }
   
    bool is_draw() { return (this->n_moves == 9 && !Over); }
  
    bool game_is_over() { return is_draw(); }
   
};

template <typename T>
class Misere_Player : public Player<T>
{
private:

    bool is_valid_input(string &input)
    {
        cout << "\nEnter your move x and y (0 to 2) separated by spaces: ";
        getline(cin >> ws, input);
        if (input.size() != 3)
            return false;
        if (isdigit(input.at(0)) &&
            isdigit(input.at(2)) &&
            (input.at(1) == ' '))
            return true;
        return false;
    }

    void get_valid_input(int &x, int &y)
    {
        string input;
        while (!is_valid_input(input))
        {
            cout << "\nInvalid input.\n";
        }
        x = input.at(0) - 48;
        y = input.at(2) - 48;
    }
  

public:
    Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

    Misere_Player(T symbol) : Player<T>(symbol) {}
   
    void getmove(int &x, int &y)
    {
        if (Over)
            return;
        get_valid_input(x, y);
    }
};

template <typename T>
class Random_Misere_Player : public RandomPlayer<T>
{
public:
    Random_Misere_Player(string name, T symbol) : RandomPlayer<T>(symbol)
    {
        this->name = name;
        this->name += "Random Compter";
        srand(static_cast<unsigned int>(time(0)));
    }
   
    void getmove(int &x, int &y)
    {
        if (Over)
            return;
        x = rand() % 3;
        y = rand() % 3;
    }
};
