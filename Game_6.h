#pragma once
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
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
                 if (this->board[i][j] != 0)
                    cout << this->board[i][j] << " |";
                else
                    cout << "  |";
            }
            cout << "\n-------------------------------";
        }
        cout << endl;
    }
    bool update_board(int x, int y, char symbol)
    {
        if (symbol == 0)
        {
            Over = false;
            this->n_moves--;
            this->board[x][y] = symbol;
            return true;
        }
        if (Over)
            return true;
        if (!is_valid_move(x, y))
            return false;
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
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

// AI player Class
template <typename T>
class Misere_AI_Player : public Player<T>
{
private:

    int calc_MiniMax(T Symbol, bool MAX)
    {
        if (this->boardPtr->is_win() || Over)
            return MAX ? -1 : 1;
        if (this->boardPtr->is_draw())
            return 0;
        int bestValue = MAX ? numeric_limits<int>::min() : numeric_limits<int>::max();
        T opponentSymbol = (Symbol == 'X') ? 'O' : 'X';
        for (short i = 0; i < 3; ++i)
        {
            for (short j = 0; j < 3; ++j)
            {
                if (this->boardPtr->update_board(i, j, Symbol))
                {
                    int value = calc_MiniMax(opponentSymbol, !MAX);
                    this->boardPtr->update_board(i, j, 0);
                    if (MAX)
                        bestValue = max(value, bestValue);
                    else
                        bestValue = min(value, bestValue);
                }
            }
        }
        return bestValue;
    }

    void getBestMove(int &x, int &y)
    {
        int bestValue = numeric_limits<int>::max();
        T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';
        
        for (short i = 0; i < 3; ++i)
        {
            for (short j = 0; j < 3; ++j)
            {
                if (this->boardPtr->update_board(i, j, this->symbol))
                {
                    int moveValue = calc_MiniMax(opponentSymbol, false);
                    this->boardPtr->update_board(i, j, 0);
                    if (moveValue < bestValue)
                    {
                        bestValue = moveValue;
                        x = i;
                        y = j;
                    }
                }
            }
        }
    }
    

public:
   
    Misere_AI_Player(string name, T symbol) : Player<T>(symbol)
    {
        this->name = name;
        this->name += " (AI Player)";
    }
    
    void getmove(int &x, int &y)
    {
        if (Over)
            return;
        getBestMove(x, y);
    }
    
};
