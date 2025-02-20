/*
    Mini-Max algorithm function
*/
#include "tictactoe.h"
#include <stdexcept>
#include <optional>

/*#define COORDINATE std::tuple<int, int>*/

using COORDINATE = std::tuple<int, int>;

std::tuple<int, std::optional<COORDINATE>> minimax(TicTacToe& state, int depth, bool isMaximizing) {
    if (depth == 0 || state.hasBeenWon() || state.planeHasBeenFilled()) {
        return std::make_tuple(state.getStateScore(), std::nullopt);
    }

    std::optional<COORDINATE> bestMove;
    
    if (isMaximizing) {
        int maxEval = -1; // Worst case for maximizing
        for (const COORDINATE& move : state.getAllPossibleMoves()) {
            int row, col;
            std::tie(row, col) = move;

            TicTacToe new_board = state.place(row, col).unwrap();
            int score;
            std::optional<COORDINATE> _;
            std::tie(score, _) = minimax(new_board, depth - 1, false);

            if (score > maxEval) {
                maxEval = score;
                bestMove = move;
            }
        }
        return std::make_tuple(maxEval, bestMove);
    } else {
        int minEval = 1; // Worst case for minimizing
        for (const COORDINATE& move : state.getAllPossibleMoves()) {
            int row, col;
            std::tie(row, col) = move;

            TicTacToe new_board = state.place(row, col).unwrap();
            int score;
            std::optional<COORDINATE> _;
            std::tie(score, _) = minimax(new_board, depth - 1, true);

            if (score < minEval) {
                minEval = score;
                bestMove = move;
            }
        }
        return std::make_tuple(minEval, bestMove);
    }
}

