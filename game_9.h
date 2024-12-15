#pragma once

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Ultimate_Board : public Board<T>
{
private:
    vector<vector<T>> Boards;   
    vector<bool> closed;        
    bool is_valid_move(short x, short y);
    bool FinalWin();
    void AddWinner(int i, T symbol);
    void InnerWin();
    bool CheckBoardWin(vector<char>& b, T& s);

public:
    Ultimate_Board();
    void display_board();
    bool update_board(int x, int y, char symbol);
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Ultimate_Player : public Player<T>
{
private:
    bool is_valid_input(string& input);
    void get_valid_input(int& x, int& y);

public:
    Ultimate_Player(string name, T symbol);
    Ultimate_Player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Random_Ultimate_Player : public RandomPlayer<T>
{
public:
    Random_Ultimate_Player(string name, T symbol);
    void getmove(int& x, int& y);
};
