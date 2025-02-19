// A tic tac toe game with the mini-max algorithm

#include <iostream>
/*#include <cctype>*/
/*#include <algorithm> // contains all_of any_of none_of*/
/*#include <cstdint>*/
/*#include <array>*/
/*#include <variant>*/
/*#include <string>*/
/*#include <optional>*/
// #include "result.h"
#include "minimax.h"
#include "options.h"
#include <stdexcept>
/*#include <optional>*/

std::string input(auto& prompt) {
    std::cout << prompt;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

void clear() {
    std::cout << "\x1B[2J\x1B[1;1H";
}

Result<std::tuple<int, int>, std::string> parse_input(std::string& response) {
    if (response.empty()) {
        return std::string("Please provide a coordiante");
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
            col = 0;
            break;
        case 'b':
            col = 1;
            break;
        case 'c':
            col = 2;
            break;
        default:
            return std::string("Invalid column");
    }
    return std::make_tuple(row - 1, col);
};

void multiplayer() {
    TicTacToe game;
    clear();
    std::cout << "Provide coordinate with {NUMBER}{LETTER}.\n";
    std::cout << game.display() << std::endl;
    while (!game.hasBeenWonned()) {
        std::cout << '\n' << "Its player '" << game.getCurrentPlayer() << "' turn" << std::endl;
        std::string selection = input("Coordinate: ");
        auto result = parse_input(selection);
        if (result.is_err()) {
            std::cerr << result.unwrap_err() << std::endl;
            continue;
        }
        int row;
        int col;
        std::tie(row, col) = result.unwrap();
        {
            auto result = game.place(row, col);
            if (result.is_err()) {
                std::cerr << result.unwrap_err() << std::endl;
                continue;
            }
        }
        clear();
        std::cout << "Provide coordinate with {NUMBER}{LETTER}.\n";
        std::cout << game.display() << std::endl;
    }
    std::cout << "'" << game.getPreviousPlayer() << "' player has won!" << std::endl;
}

void solo() {
    TicTacToe game;
    throw std::runtime_error("Haven implemented the solo game mode!");
}

std::string getGameMode() {
    std::vector<std::string> opts = {"multiplayer", "solo"};
    Options options(opts);
    while (true) {
        std::cout << options.display() << std::endl;
        std::string choice = input("\nChoice: ");
        std::optional<std::string> result = options.eval(choice);
        if (result.has_value()) {
            return result.value();
        } else {
            continue;
        }
    }
}

int main() {
    std::string game_mode = getGameMode();
    if (game_mode == "multiplayer") {
        multiplayer();
    } else if (game_mode == "solo") {
        solo();
    }
    return 0;
}
