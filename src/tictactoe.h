#include "result.h"


class TicTacToe {
    /*std::array<std::array<uint8, LENGTH>, WIDTH> __plane;*/
    int __plane[3][3];
    char __player;

public:
    TicTacToe() {
        __player = 'X';
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                __plane[r][c] = ' ';
            }
        }
    }

    Result<int, std::string> place(int row, int col) {
        if (__plane[row][col] == 'O' || __plane[row][col] == 'X') {
            return std::string("Coordinate has already been placed");
        }
        if (__player == 'X') {
            __plane[row][col] = 'X';
            __player = 'O';
        } else {
            __plane[row][col] = 'O';
            __player = 'X';
        }
        return 0;
    }

    char getCurrentPlayer() const {
        return __player;
    }

    bool hasBeenWonned() const {
        // diagonal wins
        if (__plane[0][0] != ' ' && __plane[0][0] == __plane[1][1] && __plane[1][1] == __plane[2][2]) {
            return true;
        } else if (__plane[0][2] != ' ' && __plane[0][2] == __plane[1][1] && __plane[1][1] == __plane[2][0]) {
            return true;
        }
        // horizontal wins
        for (int row = 0; row < 2; ++row) {
            if (__plane[row][0] != ' ' && __plane[row][0] == __plane[row][1] && __plane[row][1] == __plane[row][2]) {
                return true;
            }
        }
        // vertical wins
        for (int col = 0; col < 2; ++col) {
            if (__plane[0][col] != ' ' && __plane[0][col] == __plane[1][col] && __plane[1][col] == __plane[2][col]) {
                return true;
            }
        }
        return false;
    }

    char getPreviousPlayer() const {
        if (__player == 'X') {
            return 'O';
        }
        return 'X';
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
