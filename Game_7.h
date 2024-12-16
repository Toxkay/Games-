#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>

int newX = -1;
int newY = -1;
using namespace std;

template <typename T>
class Board4x4 : public Board<T>
{

private:
    vector<vector<T>> boards;

    bool checkWinRow()
    {
        // ! horizontal
        for (short i = 0; i < 4; i++)
        {
            for (short j = 0; j < 2; j++)
            {
                if ((boards.at(i).at(j) == boards.at(i).at(j + 1)) && (boards.at(i).at(j) == boards.at(i).at(j + 2)) && (boards.at(i).at(j) != 0))
                    return true;
            }
        }
        return false;
    }

    bool checkWinCol()
    {
        // ! vertical
        for (short i = 0; i < 2; i++)
        {
            for (short j = 0; j < 4; j++)
            {
                if ((boards.at(i).at(j) == boards.at(i + 1).at(j)) && (boards.at(i).at(j) == boards.at(i + 2).at(j)) && (boards.at(i).at(j) != 0))
                    return true;
            }
        }
        return false;
    }

    bool checkWinDiagonals()
    {
        // ! off Diagonal
        for (short i = 0; i < 2; i++)
        {
            for (short j = 2; j < 4; j++)
            {
                if ((boards.at(i).at(j) == boards.at(i + 1).at(j - 1)) && (boards.at(i).at(j) == boards.at(i + 2).at(j - 2)) && (boards.at(i).at(j) != 0))
                    return true;
            }
        }
        // ! principal Diagonal
        for (short i = 0; i < 2; i++)
        {
            for (short j = 1; j >= 0; j--)
            {
                if ((boards.at(i).at(j) == boards.at(i + 1).at(j + 1)) && (boards.at(i).at(j) == boards.at(i + 2).at(j + 2)) && (boards.at(i).at(j) != 0))
                    return true;
            }
        }
        return false;
    }

    bool isValidMove(int x, int y, int newX, int newY, T symbol)
    {
        if (newX < 0 || newX >= 4 || newY < 0 || newY >= 4)
            return false;

        if (abs(newX - x) + abs(newY - y) != 1)
            return false;

        if ((boards.at(newX).at(newY) == 0) && (boards.at(x).at(y) == symbol))
            return true;
        return false;
    }

public:
    Board4x4()
    {
        newX = -1;
        newY = -1;
        this->rows = this->columns = 4;
        vector<T> temp;
        for (int i = 0; i < 4; i++)
        {
            boards.push_back(temp);
            for (int j = 0; j < 4; j++)
            {
                boards.at(i).push_back(0);
            }
        }
        boards.at(0) = {'O', 'X', 'O', 'X'};
        boards.at(3) = {'X', 'O', 'X', 'O'};
        this->n_moves = 0;
    }
    void display_board()
    {
        for (int i = 0; i < this->rows; i++)
        {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++)
            {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << boards.at(i).at(j) << " |";
            }
            cout << "\n--------------------------------------";
        }
        cout << endl;
    }
    bool update_board(int x, int y, T symbol)
    {
        if (!isValidMove(x, y, newX, newY, symbol))
        {
            cout << "Invalid move. Try again.\n";
            return false;
        }
        boards.at(newX).at(newY) = symbol;
        boards.at(x).at(y) = 0;
        this->n_moves++;
        return true;
    }

    bool is_win()
    {
        if (checkWinRow() || checkWinCol() || checkWinDiagonals())
            return true;
        return false;
    }
    bool is_draw()
    {
        return (this->n_moves == 16 && !is_win());
    }

    bool game_is_over()
    {
        return (is_draw() || is_win());
    }
};
template <typename T>
class Player4x4 : public Player<T>
{
    bool is_valid_input(string &input)
    {
        cout << "\nEnter your move x and y (0 to 3) separated by spaces: ";
        getline(cin >> ws, input);
        if (input.size() != 3)
            return false;
        if ((input.at(0) >= 48 && input.at(0) <= 51) &&
            (input.at(0) >= 48 && input.at(0) <= 51) &&
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
    Player4x4(string name, T symbol) : Player<T>(name, symbol) {}
    Player4x4(T symbol) : Player<T>(symbol) {}
    void getmove(int &x, int &y)
    {
        cout << "Current Position: ";
        get_valid_input(x, y);
        cout << "New Position: ";
        get_valid_input(newX, newY);
    }
};

template <typename T>
class RandomPlayer4x4 : public RandomPlayer<T>
{
public:
    RandomPlayer4x4(string name, T symbol) : RandomPlayer<T>(symbol)
    {
        this->name = name;
        this->name += "(Random Computer)";
        srand(static_cast<unsigned int>(time(0)));
    }
    void getmove(int &x, int &y)
    {
        x = rand() % 4;
        y = rand() % 4;
        do
        {
            newX = x + (rand() % 3 - 1);
            newY = y + (rand() % 3 - 1);
        } while (!((newX >= 0 && newX < 4 && newY >= 0 && newY < 4) && abs(newX - x) + abs(newY - y) == 1));
    }
};
