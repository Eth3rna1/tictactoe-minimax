#include <vector>
#include "result.h"


class TicTacToe {
    int __plane[3][3];
    char __player;

public:
    TicTacToe() : __player('O') {
        // X is the maximizer, O is the minimizer
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                __plane[r][c] = ' ';
            }
        }
    }

    Result<TicTacToe, std::string> place(int row, int col) {
        using namespace std;
        if (__plane[row][col] == 'O' || __plane[row][col] == 'X') {
            return std::string("Coordinate has already been placed");
        }
        TicTacToe game;
        {
            // update the values within the game instantiation
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    /*cout << r << " " << c << '\n';*/
                    game.__plane[r][c] = __plane[r][c];
                }
            }
        }
        if (__player == 'X') {
            game.__plane[row][col] = 'X';
            game.__player = 'O';
        } else {
            game.__plane[row][col] = 'O';
            game.__player = 'X';
        }
        return game;
    }

    char getCurrentPlayer() const {
        return __player;
    }

    bool planeHasBeenFilled() const {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (__plane[r][c] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<std::tuple<int, int>> getAllPossibleMoves() const {
        std::vector<std::tuple<int, int>> moves;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (__plane[row][col] == ' ') {
                    moves.push_back(std::make_tuple(row, col));
                }
            }
        }
        return moves;
    }

    int getStateScore() const {
        if (hasBeenWon()) {
            return getPreviousPlayer() == 'X' ? 1 : -1;
        }
        // means a tie or game is not over yet
        return 0;
    }

    bool hasBeenWon() const {
        // diagonal wins
        if (__plane[0][0] != ' ' && __plane[0][0] == __plane[1][1] && __plane[1][1] == __plane[2][2]) {
            return true;
        } else if (__plane[0][2] != ' ' && __plane[0][2] == __plane[1][1] && __plane[1][1] == __plane[2][0]) {
            return true;
        }
        // horizontal wins
        for (int row = 0; row < 3; ++row) {
            if (__plane[row][0] != ' ' && __plane[row][0] == __plane[row][1] && __plane[row][1] == __plane[row][2]) {
                return true;
            }
        }
        // vertical wins
        for (int col = 0; col < 3; ++col) {
            if (__plane[0][col] != ' ' && __plane[0][col] == __plane[1][col] && __plane[1][col] == __plane[2][col]) {
                return true;
            }
        }
        return false;
    }

    char getPreviousPlayer() const {
        return __player == 'X' ? 'O' : 'X';
    }

    std::string display() const {
        std::string buffer = "";
        char letters[3] = {'a', 'b', 'c'};
        std::string line;
        for (int row = 0; row < 3; ++row) {
            buffer += std::to_string(row + 1);
            buffer += " ";
            /*buffer += " | | ";*/
            for (int col = 0; col < 3; ++col) {
                line += " ";
                line += __plane[row][col];
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
};
