// Filename: tictactoe.h
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 2/20/2025
//
// Description: This file contains TicTacToe's API.
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
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <tuple>
#include <vector>
#include <string>
#include "result.h"


// Tic-Tac-Toe game instance
class TicTacToe {
    char m_plane[3][3];
    char m_player;

public:
    // Constructor: player `O` is always the starting player
    TicTacToe();

    // Returns a Result, success being another instance of TicTacToe.
    // If an error occurs, such like trying to place a piece where its
    // been populated, it will return a string containing what went wrong
    Result<TicTacToe, std::string> place(int row, int col);

    // Returns the current player ('X' or 'O')
    char getCurrentPlayer() const;

    bool planeHasBeenFilled() const;

    // Returns a vector of coordiantes where such positions are empty, or have
    // not been populated
    std::vector<std::tuple<int, int>> getAllPossibleMoves() const;

    // If player `X` has won, the function will return the state score of 1,
    // else returns -1, indicating a loss, if a tie occurs or the game is
    // still being played, returns 0, indicating a neutral state
    int getStateScore() const;

    // Checks for diagonal, vertical, horizontal wins
    bool hasBeenWon() const;

    // Returns the previous instance of player (`X` or `O`)
    char getPreviousPlayer() const;

    // Displays the Tic Tac Toe UI with its labels regarding
    // its X coordiantes and Y coordiantes
    std::string display() const;
};

#endif
