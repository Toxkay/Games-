#pragma once
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>
using namespace std;

template <typename T>
class SUS_Board : public Board<T> {
private:
    vector<vector<T>> Boards; 

    bool is_valid_move(int x, int y) const {
        return x >= 0 && x < 3 && y >= 0 && y < 3 && Boards[x][y] == ' ';
    }

    bool check_sus_sequence(char symbol) const {
        for (int i = 0; i < 3; i++) {
            if ((Boards[i][0] == symbol && Boards[i][1] == 'U' && Boards[i][2] == symbol) ||
                (Boards[0][i] == symbol && Boards[1][i] == 'U' && Boards[2][i] == symbol)) {
                return true;
            }
        }
        if ((Boards[0][0] == symbol && Boards[1][1] == 'U' && Boards[2][2] == symbol) ||
            (Boards[0][2] == symbol && Boards[1][1] == 'U' && Boards[2][0] == symbol)) {
            return true;
        }
        return false;
    }

public:
    SUS_Board() {
        Boards.resize(3, vector<T>(3, ' ')); 
    }

    void display_board() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << (Boards[i][j] == ' ' ? '.' : Boards[i][j]) << " ";
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, T symbol) {
        if (is_valid_move(x, y)) {
            Boards[x][y] = symbol;
            return true;
        }
        return false;
    }

    bool is_win() const {
        return check_sus_sequence('S'); 
    }

    bool is_draw() const {
        for (const auto& row : Boards) {
            if (find(row.begin(), row.end(), ' ') != row.end()) {
                return false; 
            }
        }
        return true;
    }

    bool game_is_over() const {
        return is_win() || is_draw();
    }
};

template <typename T>
class SUS_Player_1: public Player<T> {
private:
    void get_valid_input(int& x, int& y) const {
        while (true) {
            cout << "Enter your move (row and column, e.g., 1 2): ";
            cin >> x >> y;
            x--; y--; 
            if (x >= 0 && x < 3 && y >= 0 && y < 3) break;
            cout << "Invalid input. Please enter valid row and column." << endl;
        }
    }

public:
    SUS_Player_1(string name, T symbol) : Player<T>(name, symbol) {}
    SUS_Player_1(T symbol) : Player<T>("", symbol) {}

    void getmove(int& x, int& y) override {
        get_valid_input(x, y);
    }
};

template <typename T>
class SUS_Player_2 : public SUS_Player_2<T> {
public:
    SUS_Player_2(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        x = rand() % 3;
        y = rand() % 3;
    }
};
