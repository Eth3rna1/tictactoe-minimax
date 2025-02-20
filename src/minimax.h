/*
    Mini-Max algorithm function
*/
#include "tictactoe.h"
#include <stdexcept>
#include <optional>

/*#define COORDINATE std::tuple<int, int>*/

using COORDINATE = std::tuple<int, int>;

using VALUE = std::tuple<int, COORDINATE>;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

/*std::tuple<int, std::optional<COORDINATE>> minimax(TicTacToe& state, int depth, bool isMaximizing) {*/
/*    if (depth == 0 || state.planeHasBeenFilled()) {*/
/*        return std::make_tuple(state.getStateScore(), std::nullopt);*/
/*    }*/
/*    if (isMaximizing) {*/
/*        int maxEval = -1;*/
/*        for (const COORDINATE& move: state.getAllPossibleMoves()) {*/
/*            int row;*/
/*            int col;*/
/*            std::tie(row, col) = move;*/
/*            TicTacToe new_board = state.place(row, col).unwrap();*/
/*            int score;*/
/*            VALUE best_move;*/
/*            std::tie(score, best_move) = minimax(new_board, depth - 1, false);*/
/*            if (maxEval < score) {*/
/*                return std::make_tuple(score, best_move);*/
/*            }*/
/*            return std::make_tuple(score, std::nullopt);*/
/*        }*/
/*    } else {*/
/*        int minEval = 1;*/
/*        for (const COORDINATE& move: state.getAllPossibleMoves()) {*/
/*            int row;*/
/*            int col;*/
/*            std::tie(row, col) = move;*/
/*            TicTacToe new_board = state.place(row, col).unwrap();*/
/*            int score;*/
/*            VALUE best_move;*/
/*            std::tie(score, best_move) = minimax(new_board, depth - 1, true);*/
/*            if (minEval > score) {*/
/*                return std::make_tuple(score, best_move);*/
/*            }*/
/*            return std::make_tuple(score, std::nullopt);*/
/*        }*/
/**/
/*    }*/
/*}*/

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

