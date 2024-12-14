#pragma once
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
template <typename T>
class Ultimate_Board : public Board<T>
{
private:
    vector<vector<T>> Boards;
    vector<bool> closed;
    bool is_valid_move(short x, short y)
    {
        if (!(closed.at(x)) && (x >= 0 && x <= 8) && (y >= 0 && y <= 8))
        {
            if (Boards.at(x).at(y) == 0)
                return true;
        }
        return false;
    }
    bool FinalWin()
    {
        if ((this->board[0][0] == this->board[0][1]) && (this->board[0][0] == this->board[0][2]) && (this->board[0][0] != 0) ||
            (this->board[1][0] == this->board[1][1]) && (this->board[1][0] == this->board[1][2]) && (this->board[1][0] != 0) ||
            (this->board[2][0] == this->board[2][1]) && (this->board[2][0] == this->board[2][2]) && (this->board[2][0] != 0) ||
            (this->board[0][0] == this->board[1][0]) && (this->board[0][0] == this->board[2][0]) && (this->board[0][0] != 0) ||
            (this->board[0][1] == this->board[1][1]) && (this->board[0][1] == this->board[2][1]) && (this->board[0][1] != 0) ||
            (this->board[0][2] == this->board[1][2]) && (this->board[0][2] == this->board[2][2]) && (this->board[0][2] != 0) ||
            (this->board[0][0] == this->board[1][1]) && (this->board[0][0] == this->board[2][2]) && (this->board[0][0] != 0) ||
            (this->board[0][2] == this->board[1][1]) && (this->board[0][2] == this->board[2][0]) && (this->board[0][2] != 0))
            return true;
        return false;
    }
  
    void AddWinner(int i, T symbol)
    {
        if (i == 0)
            this->board[0][0] = symbol;
        else if (i == 1)
            this->board[0][1] = symbol;
        else if (i == 2)
            this->board[0][2] = symbol;
        else if (i == 3)
            this->board[1][0] = symbol;
        else if (i == 4)
            this->board[1][1] = symbol;
        else if (i == 5)
            this->board[1][2] = symbol;
        else if (i == 6)
            this->board[2][0] = symbol;
        else if (i == 7)
            this->board[2][1] = symbol;
        else
            this->board[2][2] = symbol;
    }
    void InnerWin()
    {
        for (int i = 0; i < 9; i++)
        {
            T s;
            if (!closed.at(i) && CheckBoardWin(Boards.at(i), s))
            {
                AddWinner(i, s);
                closed.at(i) = true;
            }
        }
    }

    bool CheckBoardWin(vector<char> &b, T &s)
    {
        if ((b.at(0) == b.at(1)) && (b.at(0) == b.at(2)) && (b.at(0) != 0))
        {
            s = b.at(0);
            return true;
        }
        else if ((b.at(3) == b.at(4)) && (b.at(3) == b.at(5)) && (b.at(3) != 0))
        {
            s = b.at(3);
            return true;
        }
        else if ((b.at(6) == b.at(7)) && (b.at(6) == b.at(8)) && (b.at(6) != 0))
        {
            s = b.at(6);
            return true;
        }
        else if ((b.at(0) == b.at(3)) && (b.at(0) == b.at(6)) && (b.at(0) != 0))
        {
            s = b.at(0);
            return true;
        }
        else if ((b.at(1) == b.at(4)) && (b.at(1) == b.at(7)) && (b.at(1) != 0))
        {
            s = b.at(1);
            return true;
        }
        else if ((b.at(2) == b.at(5)) && (b.at(2) == b.at(8)) && (b.at(2) != 0))
        {
            s = b.at(2);
            return true;
        }
        else if ((b.at(0) == b.at(4)) && (b.at(0) == b.at(8)) && (b.at(0) != 0))
        {
            s = b.at(0);
            return true;
        }
        else if ((b.at(2) == b.at(4)) && (b.at(2) == b.at(6)) && (b.at(2) != 0))
        {
            s = b.at(2);
            return true;
        }
        return false;
    }

public:
    Ultimate_Board()
    {
        this->rows = this->columns = 3;
        this->board = new char *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++)
            {
                this->board[i][j] = 0;
                vector<char> temp;
                for (int k = 0; k < 9; k++)
                {
                    temp.push_back(0);
                    closed.push_back(false);
                }
                Boards.push_back(temp);
            }
        }
        this->n_moves = 0;
    }
    void display_board()
    {
        cout << "\n-----------------------------------------------------------------------------";
        for (int i = 0; i < 9; i += 3)
        {
            for (int k = 0; k < 9; k += 3)
            {
                cout << "\n|";
                for (int j = 0; j < 3; j++)
                {
                    cout << "(" << i << ", " << k + j << ") ";
                    if (Boards.at(i).at(k + j) != 0)
                        cout << Boards.at(i).at(k + j) << " |";
                    else
                        cout << "  |";
                }
                cout << "| ";
                for (int j = 0; j < 3; j++)
                {
                    cout << "(" << i + 1 << ", " << k + j << ") ";
                    if (Boards.at(i + 1).at(k + j) != 0)
                        cout << Boards.at(i + 1).at(k + j) << " |";
                    else
                        cout << "  |";
                }
                cout << "| ";
                for (int j = 0; j < 3; j++)
                {
                    cout << "(" << i + 2 << ", " << k + j << ") ";
                    if (Boards.at(i + 2).at(k + j) != 0)
                        cout << Boards.at(i + 2).at(k + j) << " |";
                    else
                        cout << "  |";
                }
            }
            cout << "\n-----------------------------------------------------------------------------";
        }
        for (int i = 0; i < this->rows; i++)
        {
            cout << "\n|";
            for (int j = 0; j < this->columns; j++)
            {
                cout << "(";
                if (this->board[i][j] != 0)
                    cout << this->board[i][j] << ") |";
                else
                    cout << " ) |";
            }
            cout << "\n--------------------";
        }
        cout << endl;
    }
    bool update_board(int x, int y, char symbol)
    {
        if (!is_valid_move(x, y))
            return false;
        this->n_moves++;
        Boards.at(x).at(y) = symbol;
        InnerWin();
        return true;
    }

    bool is_win()
    {
        if (FinalWin())
            return true;
        return false;
    }
    bool is_draw() { return (this->n_moves == 81) && !is_win(); }
    bool game_is_over() { return is_draw() || is_win(); }
    
};
template <typename T>
class Ultimate_Player : public Player<T>
{
private:
    bool is_valid_input(string &input)
    {
        cout << "\nEnter your move x and y (0 to 8) separated by spaces: ";
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
    Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}
    Ultimate_Player(T symbol) : Player<T>(symbol) {}
    void getmove(int &x, int &y) { get_valid_input(x, y); }
};
template <typename T>
class Random_Ultimate_Player : public RandomPlayer<T>
{
public:
    Random_Ultimate_Player(string name, T symbol) : RandomPlayer<T>(symbol)
    {
        this->name = name;
        this->name += " Random Compter";
        srand(static_cast<unsigned int>(time(0)));
    }
    void getmove(int &x, int &y)
    {
        x = rand() % 9;
        y = rand() % 9;
    }
};
