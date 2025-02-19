// A tic tac toe game with the mini-max algorithm

#include <iostream>
#include <cctype>
/*#include <algorithm> // contains all_of any_of none_of*/
/*#include <cstdint>*/
#include <array>
#include <variant>
#include <string>
#include <optional>
#include "result.h"

const int WIDTH = 3;
const int LENGTH = 3;

class TicTacToe {
    /*std::array<std::array<uint8, LENGTH>, WIDTH> __plane;*/
    int __plane[3][3];
    char __player;

public:
    TicTacToe() {
        __player = 'X';
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                __plane[r][c] = 0;
            }
        }
    }

    void place(int row, int col) {
        if (__player == 'X') {
            __plane[row][col] = 'X';
            __player = 'O';
        } else {
            __plane[row][col] = 'O';
            __player = 'X';
        }
    }

    bool hasBeenWonned() {
        if (__plane[0][0] != ' ' && __plane[0][0] == __plane[1][1] && __plane[1][1] == __plane[2][2]) {
            return true;
        } else if (__plane[0][2] != ' ' && __plane[0][2] == __plane[1][1] && __plane[1][1] == __plane[2][0]) {
            return true;
        }
        for (int row = 0; row < 2; ++row) {
            if (__plane[row][0] != ' ' && __plane[row][0] == __plane[row][1] && __plane[row][1] == __plane[row][2]) {
                return true;
            }
        }
        for (int col = 0; col < 2; ++col) {
            if (__plane[row][0] != ' ' && __plane[0][col] == __plane[1][col] && __plane[1][col] == __plane[2][col]) {
                return true;
            }
        }
        return false;
    }

    char getPreviousPlayer() {
        if (__player == 'X') {
            return 'O';
        }
        return 'X';
    }

    std::string display() {
        std::string buffer = "";
        char letters[3] = {'a', 'b', 'c'};
        for (int row = 1; row - 1)
        return buffer;
    }
};

std::string input(std::string& prompt) {
    std::cout << prompt;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

Result<std::tuple<int, int>, std::string> parse_input(std::string& response) {
    if (response.empty()) {
        return std::string("");
    }
    if (response.length() != 2) {
        return std::string("Invalid input, syntax is {NUMBER}{LETTER}");
    }
    if (!isdigit(response[0])) {
        return std::string("Invalid input, syntax is {NUMBER}{LETTER}");
    }
    int row = std::stoi(std::string(1, response[0]));
    int col;
    switch (response[1]) {
        case 'a':
            col = 1;
            break;
        case 'b':
            col = 2;
            break;
        case 'c':
            col = 3;
            break;
        default:
            return std::string("Invalid column");
    }
    return std::make_tuple(row - 1, col);
};

int main() {
    TicTacToe game;
    std::cout << "Compiled\n";
    std::string input = "2a";
    auto result = parse_input(input);
    if (result.is_ok()) {
        int y;
        int x;
        std::tie(y, x) = result.unwrap();
        std::cout << y << " " << x << std::endl;
    }
    return 0;
}
