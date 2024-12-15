#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 6;
const int COLS = 7;
const int WIN_COUNT = 4;

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
            board[i][j] = 0;  // Initialize with 0 (empty)
        }
    }
}

template <typename T>
bool Board<T>::update_board(int col, T symbol) {
    for (int row = rows - 1; row >= 0; --row) {
        if (board[row][col] == 0) {
            board[row][col] = symbol;
            n_moves++;
            return true;
        }
    }
    return false;  // Column is full
}

template <typename T>
void Board<T>::display_board() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "[" << (board[i][j] == 0 ? ' ' : board[i][j]) << "]";
        }
        cout << endl;
    }
}

template <typename T>
bool Board<T>::is_win() {
    // Check horizontal, vertical, and diagonal lines
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] != 0) {
                // Check horizontal
                if (j + WIN_COUNT <= columns) {
                    bool win = true;
                    for (int k = 1; k < WIN_COUNT; k++) {
                        if (board[i][j] != board[i][j + k]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return true;
                }
                // Check vertical
                if (i + WIN_COUNT <= rows) {
                    bool win = true;
                    for (int k = 1; k < WIN_COUNT; k++) {
                        if (board[i][j] != board[i + k][j]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return true;
                }
                // Check diagonal (bottom-left to top-right)
                if (i + WIN_COUNT <= rows && j + WIN_COUNT <= columns) {
                    bool win = true;
                    for (int k = 1; k < WIN_COUNT; k++) {
                        if (board[i][j] != board[i + k][j + k]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return true;
                }
                // Check diagonal (top-left to bottom-right)
                if (i - WIN_COUNT + 1 >= 0 && j + WIN_COUNT <= columns) {
                    bool win = true;
                    for (int k = 1; k < WIN_COUNT; k++) {
                        if (board[i][j] != board[i - k][j + k]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return true;
                }
            }
        }
    }
    return false;
}

template <typename T>
bool Board<T>::is_draw() {
    return n_moves == rows * columns;
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
void Player<T>::getmove(int& col) {
    do {
        cout << "Enter column (0 to " << COLS - 1 << "): ";
        cin >> col;
    } while (col < 0 || col >= COLS);
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
    int col;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i = 0; i < 2; i++) {
            cout << players[i]->getname() << "'s turn (" << players[i]->getsymbol() << "):\n";
            players[i]->getmove(col);
            while (!boardPtr->update_board(col, players[i]->getsymbol())) {
                players[i]->getmove(col);
            }
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

    Board<char> board(ROWS, COLS);
    Player<char>* players[2];
    players[0] = new Player<char>("Player 1", 'X');
    players[1] = new Player<char>("Player 2", 'O');

    for (int i = 0; i < 2; i++) {
        players[i]->setBoard(&board);
    }

    GameManager<char> game(&board, players);
    game.run();

    return 0;
}
