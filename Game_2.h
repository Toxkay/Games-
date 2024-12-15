#pragma once
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>

using namespace std;


template <typename T>
class ConnectFourBoard {
private:
    vector<vector<T>> board;
    int rows = 6;
    int cols = 7;
    bool is_valid_move(int col);
    bool check_win();
    bool check_vertical();
    bool check_horizontal();
    bool check_diagonal();

public:
    ConnectFourBoard();
    void print_board();
    bool drop_piece(int col, T symbol);
    bool game_over();
    bool is_draw();
    bool is_win();
};


template <typename T>
ConnectFourBoard<T>::ConnectFourBoard() {
    board.resize(rows, vector<T>(cols, ' ')); 
}

template <typename T>
void ConnectFourBoard<T>::print_board() {
    cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "-----------------------------" << endl;
}

template <typename T>
bool ConnectFourBoard<T>::is_valid_move(int col) {
    return (col >= 0 && col < cols && board[0][col] == ' ');
}

template <typename T>
bool ConnectFourBoard<T>::drop_piece(int col, T symbol) {
    if (!is_valid_move(col)) {
        return false;
    }

    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = symbol;
            break;
        }
    }
    return true;
}

template <typename T>
bool ConnectFourBoard<T>::check_win() {
    return check_vertical() || check_horizontal() || check_diagonal();
}

template <typename T>
bool ConnectFourBoard<T>::check_vertical() {
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows - 3; row++) {
            if (board[row][col] != ' ' && board[row][col] == board[row + 1][col] && board[row][col] == board[row + 2][col] && board[row][col] == board[row + 3][col]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ConnectFourBoard<T>::check_horizontal() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (board[row][col] != ' ' && board[row][col] == board[row][col + 1] && board[row][col] == board[row][col + 2] && board[row][col] == board[row][col + 3]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ConnectFourBoard<T>::check_diagonal() {
    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (board[row][col] != ' ' && board[row][col] == board[row + 1][col + 1] && board[row][col] == board[row + 2][col + 2] && board[row][col] == board[row + 3][col + 3]) {
                return true;
            }
        }
        for (int col = 3; col < cols; col++) {
            if (board[row][col] != ' ' && board[row][col] == board[row + 1][col - 1] && board[row][col] == board[row + 2][col - 2] && board[row][col] == board[row + 3][col - 3]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ConnectFourBoard<T>::is_draw() {
    for (int col = 0; col < cols; col++) {
        if (board[0][col] == ' ') {
            return false;
        }
    }
    return !check_win();
}

template <typename T>
bool ConnectFourBoard<T>::game_over() {
    return is_win() || is_draw();
}

template <typename T>
bool ConnectFourBoard<T>::is_win() {
    return check_win();
}

template <typename T>
class ConnectFourPlayer {
private:
    string name;
    T symbol;

public:
    ConnectFourPlayer(string player_name, T player_symbol);
    void make_move(ConnectFourBoard<T>& board, int col);
    string get_name();
    T get_symbol();
};

template <typename T>
ConnectFourPlayer<T>::ConnectFourPlayer(string player_name, T player_symbol) : name(player_name), symbol(player_symbol) {}

template <typename T>
void ConnectFourPlayer<T>::make_move(ConnectFourBoard<T>& board, int col) {
    if (board.drop_piece(col, symbol)) {
        cout << name << " placed " << symbol << " in column " << col << endl;
    } else {
        cout << "Column " << col << " is full. Try again!" << endl;
    }
}

template <typename T>
string ConnectFourPlayer<T>::get_name() {
    return name;
}

template <typename T>
T ConnectFourPlayer<T>::get_symbol() {
    return symbol;
}

template <typename T>
class RandomConnectFourPlayer : public ConnectFourPlayer<T> {
public:
    RandomConnectFourPlayer(string player_name, T player_symbol);
    void make_move(ConnectFourBoard<T>& board);
};
template <typename T>
RandomConnectFourPlayer<T>::RandomConnectFourPlayer(string player_name, T player_symbol) : ConnectFourPlayer<T>(player_name, player_symbol) {}

template <typename T>
void RandomConnectFourPlayer<T>::make_move(ConnectFourBoard<T>& board) {
    srand(time(0));
    int col;
    do {
        col = rand() % 7; 
    } while (!board.drop_piece(col, get_symbol()));
    cout << "Random player placed " << get_symbol() << " in column " << col << endl;
}
