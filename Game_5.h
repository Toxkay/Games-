#pragma once
#include "BoardGame_Classes.h"
#include <bits\stdc++.h>

using namespace std;

template <typename T>
class NumericalTicTacToe
{
private:
    T board[3][3];  
    vector<T> available_numbers;  

    bool check_win(T player)
    {
        for (int i = 0; i < 3; i++)
        {
    
            if (board[i][0] + board[i][1] + board[i][2] == 15)
                return true;

            if (board[0][i] + board[1][i] + board[2][i] == 15)
                return true;
        }

        if (board[0][0] + board[1][1] + board[2][2] == 15)
            return true;
        if (board[0][2] + board[1][1] + board[2][0] == 15)
            return true;

        return false;
    }

    bool check_draw()
    {
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == 0)
                    return false;
        return true;
    }

    bool is_valid_move(int x, int y)
    {
        return x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == 0;
    }

public:
    NumericalTicTacToe()
    {
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = 0;

        
        for (int i = 1; i <= 9; i++)
            if (i % 2 == 0)
                available_numbers.push_back(i);  
            else
                available_numbers.push_back(i);  
    }

    void display_board()
    {
        cout << "\n---------\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 0)
                    cout << board[i][j] << " ";
                else
                    cout << "  ";
            }
            cout << "\n";
        }
        cout << "---------\n";
    }

    bool player_move(int x, int y, T num)
    {
        if (is_valid_move(x, y) && find(available_numbers.begin(), available_numbers.end(), num) != available_numbers.end())
        {
            board[x][y] = num;
            available_numbers.erase(remove(available_numbers.begin(), available_numbers.end(), num), available_numbers.end());
            return true;
        }
        return false;
    }

    bool is_winner(T player)
    {
        return check_win(player);
    }

    bool is_draw()
    {
        return check_draw();
    }

    bool game_over()
    {
        return is_winner(1) || is_winner(2) || is_draw();
    }

    T get_current_player(int turn)
    {
        return (turn % 2 == 0) ? 1 : 2;  
    }

    void play_game()
    {
        int turn = 0;
        int x, y;
        T player;

        while (!game_over())
        {
            player = get_current_player(turn);
            cout << "Player " << player << "'s turn (Enter x and y coordinates): ";
            cin >> x >> y;

            T number;
            if (player == 1)
            {
                cout << "Player 1, enter an odd number (1, 3, 5, 7, 9): ";
                cin >> number;
            }
            else
            {
                cout << "Player 2, enter an even number (2, 4, 6, 8): ";
                cin >> number;
            }

            if (!player_move(x, y, number))
            {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            display_board();
            if (is_winner(player))
            {
                cout << "Player " << player << " wins!\n";
                return;
            }

            turn++;
        }

        cout << "It's a draw!\n";
    }
};
