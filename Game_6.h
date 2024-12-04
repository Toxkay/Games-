#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;


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
   
    bool is_valid_input(string &input)
    {
        cout << "\nEnter your move x and y (0 to 2) separated by spaces: ";
        getline(cin >> ws, input);
        if (input.size() != 3)
            return false;
        if ((input.at(0) >= 48 && input.at(0) <= 57) &&
            (input.at(0) >= 48 && input.at(0) <= 57) &&
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
    // checks for a losing condition loops all over the 9 constraints
    void checkLOSE()
    {
        if ((this->board[0][0] == this->board[0][1]) && (this->board[0][0] == this->board[0][2]) && (this->board[0][0] == 'X') ||
            (this->board[1][0] == this->board[1][1]) && (this->board[1][0] == this->board[1][2]) && (this->board[1][0] == 'X') ||
            (this->board[2][0] == this->board[2][1]) && (this->board[2][0] == this->board[2][2]) && (this->board[2][0] == 'X') ||
            (this->board[0][0] == this->board[1][0]) && (this->board[0][0] == this->board[2][0]) && (this->board[0][0] == 'X') ||
            (this->board[0][1] == this->board[1][1]) && (this->board[0][1] == this->board[2][1]) && (this->board[0][1] == 'X') ||
            (this->board[0][2] == this->board[1][2]) && (this->board[0][2] == this->board[2][2]) && (this->board[0][2] == 'X') ||
            (this->board[0][0] == this->board[1][1]) && (this->board[0][0] == this->board[2][2]) && (this->board[0][0] == 'X') ||
            (this->board[0][2] == this->board[1][1]) && (this->board[0][2] == this->board[2][0]) && (this->board[0][2] == 'X'))
            this->n_moves = 99;

        if ((this->board[0][0] == this->board[0][1]) && (this->board[0][0] == this->board[0][2]) && (this->board[0][0] == 'O') ||
            (this->board[1][0] == this->board[1][1]) && (this->board[1][0] == this->board[1][2]) && (this->board[1][0] == 'O') ||
            (this->board[2][0] == this->board[2][1]) && (this->board[2][0] == this->board[2][2]) && (this->board[2][0] == 'O') ||
            (this->board[0][0] == this->board[1][0]) && (this->board[0][0] == this->board[2][0]) && (this->board[0][0] == 'O') ||
            (this->board[0][1] == this->board[1][1]) && (this->board[0][1] == this->board[2][1]) && (this->board[0][1] == 'O') ||
            (this->board[0][2] == this->board[1][2]) && (this->board[0][2] == this->board[2][2]) && (this->board[0][2] == 'O') ||
            (this->board[0][0] == this->board[1][1]) && (this->board[0][0] == this->board[2][2]) && (this->board[0][0] == 'O') ||
            (this->board[0][2] == this->board[1][1]) && (this->board[0][2] == this->board[2][0]) && (this->board[0][2] == 'O'))
            this->n_moves = 98;
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
        if (this->n_moves >= 99)
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
        if (this->n_moves >= 99)
        {
            this->n_moves++;
            return true;
        }
        if ((x == 10) && (y == 10))
        {
            get_valid_input(x, y);
            while (!is_valid_move(x, y))
            {
                get_valid_input(x, y);
            }
        }
        if (!is_valid_move(x, y))
            return false;
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
   
    bool is_win()
    {
        if ((this->n_moves == 100))
            return true;
        if (this->n_moves >= 98)
        {
            this->n_moves++;
            return false;
        }
        checkLOSE();
        return false;
    }
   
    bool is_draw() { return (this->n_moves == 9); }
   
    bool game_is_over() { return is_win() || is_draw(); }
   
};

template <typename T>
class Misere_Player : public Player<T>
{
public:
    Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}
   
    Misere_Player(T symbol) : Player<T>(symbol) {}
   
    void getmove(int &x, int &y)
    {
        x = 10;
        y = 10;
    }
};

template <typename T>
class Random_Misere_Player : public RandomPlayer<T>
{
public:
    Random_Misere_Player(string name,T symbol) : RandomPlayer<T>(symbol)
    {
        this->name= name;
        this->name+="(Random Computer)";
        srand(static_cast<unsigned int>(time(0)));
    }
   
    void getmove(int &x, int &y)
    {
        x = rand() % 3;
        y = rand() % 3;
    }
};
