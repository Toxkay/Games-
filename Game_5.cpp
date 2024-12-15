#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 3;
const int WIN_SUM = 15;

template <typename T>
Board<T>::Board(int r, int c) {
    rows = r;
    columns = c;
    board = new T*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new T[columns];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;  
        }
    }
}

template <typename T>
bool Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == 0) {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Board<T>::display_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << "[" << (board[i][j] == 0 ? ' ' : board[i][j]) << "]";
        }
        cout << endl;
    }
}

template <typename T>
bool Board<T>::is_win() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] + board[i][1] + board[i][2] == WIN_SUM) return true;
        if (board[0][i] + board[1][i] + board[2][i] == WIN_SUM) return true;
    }
    if (board[0][0] + board[1][1] + board[2][2] == WIN_SUM) return true;
    if (board[0][2] + board[1][1] + board[2][0] == WIN_SUM) return true;

    return false;
}

template <typename T>
bool Board<T>::is_draw() {
    return n_moves == SIZE * SIZE;
}

template <typename T>
bool Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Player<T>::Player(string n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

template <typename T>
Player<T>::Player(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

template <typename T>
RandomPlayer<T>::RandomPlayer(T symbol) : Player<T>(symbol) {}

template <typename T>
void Player<T>::getmove(int& x, int& y) {
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (!boardPtr->update_board(x, y, symbol));
}

template <typename T>
T Player<T>::getsymbol() {
    return symbol;
}

template <typename T>
string Player<T>::getname() {
    return name;
}

template <typename T>
void Player<T>::setBoard(Board<T>* b) {
    this->boardPtr = b;
}

template <typename T>
GameManager<T>::GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

template <typename T>
void GameManager<T>::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i = 0; i < 2; i++) {
            cout << players[i]->getname() << "'s turn (" << players[i]->getsymbol() << "):\n";
            players[i]->getmove(x, y);
            boardPtr->display_board();
            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins!\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}

int main() {
    srand(time(0));

    Board<int> board(3, 3);
    Player<int>* players[2];
    players[0] = new Player<int>("Player 1", 1);  
    players[1] = new Player<int>("Player 2", 2);  

    for (int i = 0; i < 2; i++) {
        players[i]->setBoard(&board);
    }

    GameManager<int> game(&board, players);
    game.run();

    return 0;
}
