// Filename: minimax.h
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 2/20/2025
//
// Description: This file contains the Mini-Max function algorithm.
//
// License: This file is licensed under the MIT License.
//          See the LICENSE file for more details.
//
// Dependencies:
//    System Headers: <optional>    // Used for type safety, the function "COULD" return a coordinate
//    Local Headers: "tictactoe.h"  // Mini-Max function must be able to use game state
#ifndef MINIMAX_H
#define MINIMAX_H

#include <tuple>
#include <optional>
#include "tictactoe.h"

// The minimax algorithm to check for the best move for the AI
std::tuple<int, std::optional<std::tuple<int, int>>> minimax(TicTacToe& state, int depth, bool isMaximizing);

#endif
