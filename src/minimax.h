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

#include "tictactoe.h"
#include <optional>

// The minimax algorithm to check for the best move for the AI
std::tuple<int, std::optional<std::tuple<int, int>>> minimax(TicTacToe& state, int depth, bool isMaximizing) {
    if (depth == 0 || state.hasBeenWon() || state.planeHasBeenFilled()) {
        return std::make_tuple(state.getStateScore(), std::nullopt);
    }

    std::optional<std::tuple<int, int>> bestMove;
    
    if (isMaximizing) {
        int maxEval = -1; // Worst case for maximizing
        for (const std::tuple<int, int>& move : state.getAllPossibleMoves()) {
            int row, col;
            std::tie(row, col) = move;

            TicTacToe new_board = state.place(row, col).unwrap();
            int score;
            std::optional<std::tuple<int, int>> _;
            std::tie(score, _) = minimax(new_board, depth - 1, false);

            if (score > maxEval) {
                maxEval = score;
                bestMove = move;
            }
        }
        return std::make_tuple(maxEval, bestMove);
    } else {
        int minEval = 1; // Worst case for minimizing
        for (const std::tuple<int, int>& move : state.getAllPossibleMoves()) {
            int row, col;
            std::tie(row, col) = move;

            TicTacToe new_board = state.place(row, col).unwrap();
            int score;
            std::optional<std::tuple<int, int>> _;
            std::tie(score, _) = minimax(new_board, depth - 1, true);

            if (score < minEval) {
                minEval = score;
                bestMove = move;
            }
        }
        return std::make_tuple(minEval, bestMove);
    }
}

#endif
