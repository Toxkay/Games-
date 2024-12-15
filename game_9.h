#pragma once

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

int get_pos_integer(const string& prompt) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        cin >> input;
        if (!all_of(input.begin(), input.end(), ::isdigit)) {
            cout << "Please enter a valid positive integer." << endl;
            continue;
        }
        value = stoi(input);
        if (value <= 0) {
            cout << "Please enter a valid positive integer." << endl;
        } else {
            break;
        }
    }
    return value;
}


bool is_valid_move(int x, int y, vector<vector<char>>& board) {
    return x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ';
}


bool check_sus_sequence(vector<vector<char>>& board, char symbol) {
    for (int i = 0; i < 3; i++) {
        
        if (board[i][0] == symbol && board[i][1] == 'U' && board[i][2] == symbol) return true;
        
        if (board[0][i] == symbol && board[1][i] == 'U' && board[2][i] == symbol) return true;
    }
    
    if (board[0][0] == symbol && board[1][1] == 'U' && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == 'U' && board[2][0] == symbol) return true;

    return false;
}

template <typename T>
class Ultimate_Board : public Board<T> {
private:
    vector<vector<T>> Boards; 

    bool is_valid_move(short x, short y) {
        return x >= 0 && x < 3 && y >= 0 && y < 3 && Boards[x][y] == ' ';
    }

    bool CheckBoardWin(vector<char>& b, T& s) {
        return check_sus_sequence(Boards, s);
    }

public:
    Ultimate_Board() {
        
        Boards.resize(3, vector<T>(3, ' '));
    }

    void display_board() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << (Boards[i][j] == ' ' ? '.' : Boards[i][j]) << " ";
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, char symbol) {
        if (is_valid_move(x, y)) {
            Boards[x][y] = symbol;
            return true;
        }
        return false;
    }

    bool is_win() {
        return check_sus_sequence(Boards, 'S');
    }

    bool is_draw() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (Boards[i][j] == ' ') return false;
            }
        }
        return true;
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }
};

template <typename T>
class Ultimate_Player : public Player<T> {
private:
    
    bool is_valid_input(string& input) {
        return (input == "S" || input == "U");
    }

    void get_valid_input(int& x, int& y) {
        while (true) {
            cout << "Enter your move (row and column, e.g., 1 2): ";
            cin >> x >> y;
            x--; y--; 
            if (x >= 0 && x < 3 && y >= 0 && y < 3) break;
            cout << "Invalid input. Please enter valid row and column." << endl;
        }
    }

public:
    Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}
    Ultimate_Player(T symbol) : Player<T>("", symbol) {}

    void getmove(int& x, int& y) {
        get_valid_input(x, y);
    }
};

template <typename T>
class Random_Ultimate_Player : public RandomPlayer<T> {
public:
    Random_Ultimate_Player(string name, T symbol) : RandomPlayer<T>(name, symbol) {}

    void getmove(int& x, int& y) {
        x = rand() % 3;
        y = rand() % 3;
    }
};
