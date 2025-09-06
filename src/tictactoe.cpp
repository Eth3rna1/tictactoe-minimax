// Filename: tictactoe.cpp
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 9/6/2025
//
// Description: Implementation file contains TicTacToe's API.
//
// License: This file is licensed under the MIT License.
//          See the LICENSE file for more details.
//
// Dependencies:
//    System Headers: 
//        - <vector>     // Functionality to store a success or error value
//
//    Local Headers:
//        - "result.h"   // Used for type safety, to efficiently handle error cases
#include <tuple>
#include <vector>
#include <string>
#include "../include/result.h"
#include "../include/tictactoe.h"


// Constructor: player `O` is always the starting player
TicTacToe::TicTacToe() : m_player('O') {
    // X is the maximizer, O is the minimizer
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            m_plane[r][c] = ' ';
        }
    }
}

// Returns a Result, success being another instance of TicTacToe.
// If an error occurs, such like trying to place a piece where its
// been populated, it will return a string containing what went wrong
Result<TicTacToe, std::string> TicTacToe::place(int row, int col) {
    using namespace std;
    if (m_plane[row][col] == 'O' || m_plane[row][col] == 'X') {
        return std::string("Coordinate has already been placed");
    }
    TicTacToe game;
    {
        // update the values within the game instantiation
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                /*cout << r << " " << c << '\n';*/
                game.m_plane[r][c] = m_plane[r][c];
            }
        }
    }
    if (m_player == 'X') {
        game.m_plane[row][col] = 'X';
        game.m_player = 'O';
    } else {
        game.m_plane[row][col] = 'O';
        game.m_player = 'X';
    }
    return game;
}

// Returns the current player ('X' or 'O')
char TicTacToe::getCurrentPlayer() const {
    return m_player;
}

bool TicTacToe::planeHasBeenFilled() const {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (m_plane[r][c] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Returns a vector of coordiantes where such positions are empty, or have
// not been populated
std::vector<std::tuple<int, int>> TicTacToe::getAllPossibleMoves() const {
    std::vector<std::tuple<int, int>> moves;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (m_plane[row][col] == ' ') {
                moves.push_back(std::make_tuple(row, col));
            }
        }
    }
    return moves;
}

// If player `X` has won, the function will return the state score of 1,
// else returns -1, indicating a loss, if a tie occurs or the game is
// still being played, returns 0, indicating a neutral state
int TicTacToe::getStateScore() const {
    if (hasBeenWon()) {
        return getPreviousPlayer() == 'X' ? 1 : -1;
    }
    // means a tie or game is not over yet
    return 0;
}

// Checks for diagonal, vertical, horizontal wins
bool TicTacToe::hasBeenWon() const {
    // diagonal wins
    if (m_plane[0][0] != ' ' && m_plane[0][0] == m_plane[1][1] && m_plane[1][1] == m_plane[2][2]) {
        return true;
    } else if (m_plane[0][2] != ' ' && m_plane[0][2] == m_plane[1][1] && m_plane[1][1] == m_plane[2][0]) {
        return true;
    }
    // horizontal wins
    for (int row = 0; row < 3; ++row) {
        if (m_plane[row][0] != ' ' && m_plane[row][0] == m_plane[row][1] && m_plane[row][1] == m_plane[row][2]) {
            return true;
        }
    }
    // vertical wins
    for (int col = 0; col < 3; ++col) {
        if (m_plane[0][col] != ' ' && m_plane[0][col] == m_plane[1][col] && m_plane[1][col] == m_plane[2][col]) {
            return true;
        }
    }
    return false;
}

// Returns the previous instance of player (`X` or `O`)
char TicTacToe::getPreviousPlayer() const {
    return m_player == 'X' ? 'O' : 'X';
}

// Displays the Tic Tac Toe UI with its labels regarding
// its X coordiantes and Y coordiantes
std::string TicTacToe::display() const {
    std::string buffer = "";
    char letters[3] = {'a', 'b', 'c'};
    std::string line;
    for (int row = 0; row < 3; ++row) {
        buffer += std::to_string(row + 1);
        buffer += " ";
        for (int col = 0; col < 3; ++col) {
            line += " ";
            line += m_plane[row][col];
            line += " ";
            if (col < 2) {
                line += "|";
            }
        } 
        buffer += line;
        line.clear();
        if (row != 2) {
            buffer += "\n  -----------\n";
        }
    }
    buffer += "\n   a   b   c";
    return buffer;
}
