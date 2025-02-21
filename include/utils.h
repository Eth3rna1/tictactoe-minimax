// Filename: utils.h
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 2/21/2025
//
// Description: This file contains minor functions
//
// License: This file is licensed under the MIT License.
//          See the LICENSE file for more details.
//
// Dependencies:
//      System Headers:
//          - <iostream>   // For standard input and output
//          - <tuple>      // To return X and Y coordinates in one value
//          - <vector>     // Helps to construct the Options class
//      Local Headers:
//          - "result.h"   // Contains the Result class, which stores a success case or error case
//          - "options.h"  // Used to output the UI for the client
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <tuple>
#include <vector>
#include "result.h"
#include "options.h"

// Clears the terminal screen
void clear() {
    std::cout << "\x1B[2J\x1B[1;1H";
}

// Outputs the prompt before receiving user input
std::string input(auto& prompt) {
    std::cout << prompt;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

// After making a selection on coordinate regarding the Tic Tac Toe game,
// the function will translate the input into numerical x and y coordiantes
Result<std::tuple<int, int>, std::string> parse_input(std::string& response) {
    if (response.empty()) {
        return std::string("Please provide a coordiante");
    }
    if (response.length() != 2) {
        return std::string("Please provide a valid input, {1-3}{a-c}");
    }
    if (!isdigit(response[0])) {
        return std::string("Please provide a numerical value, then a letter value: {1-3}{a-b}");
    }
    int row = std::stoi(std::string(1, response[0]));
    int col;
    switch (std::tolower(response[1])) {
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

// Outputs a list of options for the client to choose from
// and returns the choice of the client regarding their input
std::string getGameMode() {
    std::vector<std::string> opts({"soloplayer", "multiplayer"});
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

#endif
