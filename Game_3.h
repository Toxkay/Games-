#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;
bool Over = false;
template <typename T>
class Board5x5 : public Board<T>
{
private:
    short xCount = 0;
    short oCount = 0;

    void countWins(short &x, short &o)
    {
      
        //  vertical count
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 5; j++)
            {
                if ((this->board[i][j] == this->board[i + 1][j]) && (this->board[i][j] == this->board[i + 2][j]) && (this->board[i][j] == 'X'))
                    x++;
                else if ((this->board[i][j] == this->board[i + 1][j]) && (this->board[i][j] == this->board[i + 2][j]) && (this->board[i][j] == 'O'))
                    o++;
            }
        }
    
        //  horizontal count
        for (short i = 0; i < 5; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                if ((this->board[i][j] == this->board[i][j + 1]) && (this->board[i][j] == this->board[i][j + 2]) && (this->board[i][j] == 'X'))
                    x++;
                else if ((this->board[i][j] == this->board[i][j + 1]) && (this->board[i][j] == this->board[i][j + 2]) && (this->board[i][j] == 'O'))
                    o++;
            }
        }
     
        //  off Diagonal count
        for (short i = 0; i < 3; i++)
        {
            for (short j = 2; j < 5; j++)
            {
                if ((this->board[i][j] == this->board[i + 1][j - 1]) && (this->board[i][j] == this->board[i + 2][j - 2]) && (this->board[i][j] == 'X'))
                    x++;
                else if ((this->board[i][j] == this->board[i + 1][j - 1]) && (this->board[i][j] == this->board[i + 2][j - 2]) && (this->board[i][j] == 'O'))
                    o++;
            }
        }
        
        //  principal Diagonal count
        for (short i = 0; i < 3; i++)
        {
            for (short j = 2; j >= 0; j--)
            {
                if ((this->board[i][j] == this->board[i + 1][j + 1]) && (this->board[i][j] == this->board[i + 2][j + 2]) && (this->board[i][j] == 'X'))
                    x++;
                else if ((this->board[i][j] == this->board[i + 1][j + 1]) && (this->board[i][j] == this->board[i + 2][j + 2]) && (this->board[i][j] == 'O'))
                    o++;
            }
        }
       
    }
 
    bool is_valid_move(short x, short y)
    {
        if ((x >= 0 && x <= 4) && (y >= 0 && y <= 4))
        {
            if (this->board[x][y] == 0)
                return true;
        }
        return false;
    }
  

public:
    Board5x5()
    {
        Over = false;
        this->rows = this->columns = 5;
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
            cout << "\n|";
            for (int j = 0; j < this->columns; j++)
            {
                cout << "(" << i << "," << j << ") ";
                if (this->board[i][j] != 0)
                    cout << this->board[i][j] << " |";
                else
                    cout << "  |";
            }
            cout << "\n----------------------------------------------";
        }
        cout << endl;
    }
 
    bool update_board(int x, int y, char symbol)
    {
        if (Over)
        {
            this->n_moves++;
            return true;
        }
        if (!is_valid_move(x, y))
            return false;
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
  
    bool is_win()
    {
        if (this->n_moves < 24)
            return false;
        else if (this->n_moves == 24)
        {
            countWins(xCount, oCount);
            if (oCount > xCount)
                return true;
            else if (oCount == xCount)
                return false;
            Over = true;
            return false;
        }
        if (this->n_moves == 25)
            return true;
        return true;
    }
   
    bool is_draw() { return this->n_moves == 24 && !Over; }
    
    bool game_is_over() { return is_win() || is_draw(); }
   
};

template <typename T>
class Player5x5 : public Player<T>
{
private:
 
    bool is_valid_input(string &input)
    {
        cout << "\nEnter your move x and y (0 to 4) separated by spaces: ";
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
    

public:
    Player5x5(string name, T symbol) : Player<T>(name, symbol) {}
    Player5x5(T symbol) : Player<T>(symbol) {}
    void getmove(int &x, int &y)
    {
        if (Over)
            return;
        get_valid_input(x, y);
    }

};

template <typename T>
class RandomPlayer5x5 : public RandomPlayer<T>
{
public:
    RandomPlayer5x5(string name, T symbol) : RandomPlayer<T>(symbol)
    {
        this->name = name;
        this->name += "(Random Computer)";
        srand(static_cast<unsigned int>(time(0)));
    }

   
   
    void getmove(int &x, int &y)
    {
        if (Over)
            return;
        x = rand() % 5;
        y = rand() % 5;
    }
};
