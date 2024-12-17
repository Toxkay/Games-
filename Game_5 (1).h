#ifndef _NUMERICAL_TICTACTOE_H
#define _NUMERICAL_TICTACTOE_H
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
bool isOddPlayer = false;

using namespace std;

template <typename T>
class NumericalBoard : public Board<T>
{
    vector<int> even;
    vector<int> odd;

public:
    NumericalBoard();
    ~NumericalBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool check_sum_15(T a, T b, T c);
    bool checkValidNum(T symbol);
};

template <typename T>
class HumanPlayer : public Player<T>
{
public:
    HumanPlayer(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Random_Player : public RandomPlayer<T>
{
public:
    Random_Player(T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
NumericalBoard<T>::NumericalBoard()
{
    isOddPlayer = true;
    this->rows = 3;
    this->columns = 3;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    for (int i = 2; i < 10; i += 2)
    {
        even.push_back(i);
        odd.push_back(i - 1);
    }
    odd.push_back(9);
    this->n_moves = 0;
}

template <typename T>
NumericalBoard<T>::~NumericalBoard()
{
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool NumericalBoard<T>::update_board(int x, int y, T symbol)
{
    if (x >= 0 && x <= 2 && y >= 0 && y <= 2 && this->board[x][y] == 0)
    {
        if (!checkValidNum(symbol))
            return false;
        this->board[x][y] = symbol;
        this->n_moves++;
        isOddPlayer ? isOddPlayer = false : isOddPlayer = true;
        return true;
    }
    return false;
}

template <typename T>
bool NumericalBoard<T>::checkValidNum(T symbol)
{
    if (isOddPlayer)
    {
        for (int i = 0; i < odd.size(); i++)
        {
            if (odd.at(i) == symbol)
            {
                odd.erase(find(odd.begin(), odd.end(), symbol));
                return true;
            }
        }
    }
    if (!isOddPlayer)
    {
        for (int i = 0; i < even.size(); i++)
        {
            if (even.at(i) == symbol)
            {
                even.erase(find(even.begin(), even.end(), symbol));
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void NumericalBoard<T>::display_board()
{
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
        cout << "\n-------------------------------";
    }
    cout << endl;
}

template <typename T>
bool NumericalBoard<T>::is_win()
{
    for (int i = 0; i < this->rows; i++)
    {
        if (check_sum_15(this->board[i][0], this->board[i][1], this->board[i][2]))
            return true;
        if (check_sum_15(this->board[0][i], this->board[1][i], this->board[2][i]))
            return true;
    }
    if (check_sum_15(this->board[0][0], this->board[1][1], this->board[2][2]))
        return true;
    if (check_sum_15(this->board[0][2], this->board[1][1], this->board[2][0]))
        return true;
    return false;
}

template <typename T>
bool NumericalBoard<T>::is_draw()
{
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool NumericalBoard<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
bool NumericalBoard<T>::check_sum_15(T a, T b, T c)
{
    return ((a != 0) && (b != 0) && (c != 0) && (a + b + c == 15));
}
// ==========================================================

template <typename T>
HumanPlayer<T>::HumanPlayer(string name, T symbol) : Player<T>(name, symbol){};

template <typename T>
void HumanPlayer<T>::getmove(int &x, int &y)
{
    cout << "Enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "Enter your number ";
    isOddPlayer ? cout << "(1, 3, 5, 7, 9): " : cout << "(2, 4, 6, 8): ";
    cin >> this->symbol;
}

template <typename T>
Random_Player<T>::Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % 3;
    y = rand() % 3;
    int temp = (rand() % 9) + 1;
    this->symbol = temp;
}

#endif
