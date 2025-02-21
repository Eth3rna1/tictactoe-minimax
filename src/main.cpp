/* A tic tac toe game with the mini-max algorithm
 *
 * main.cpp
 *
 * Description: This file contains the main implementation of tictactoe.
 *              It initializes the application and handles the primary functionality.
 *
 * Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
 *
 * Date Created: 2/17/2025
 *
 * Last Modified: 2/20/2025
 *
 * Version: 0.0.1
 *
 * Dependencies:
 * - C++ Standard Library
 *    - iostream       // For outputting to the standard output or standard err
 *    - tuple          // For returning multiple values at once within a function
 *    - vector         // Serves as a dynamic array collecting objects
 *    - optional       // Serves as a way to indicate that the function "might" return
 *                        A value; for type safety
 * 
 * - Local Header Files
 *    - result.h       // Contains the Result class, assimilates Rust's Result API
 *    - minimax.h      // Contains the minimax function; an algorithm for decision making
 *    - options.h      // Contains the Option class; to display a list of options and
 *                        Evaluate user input
 *    - tictactoe.h    // Contains the tic-tac-toe API; game functionality
 *    
 *
 * Usage: 
 * To compile the program, use the following command:
 * g++ main.cpp -o tictactoe.exe
 * 
 * To run the program, execute:
 * tictactoe.exe
 *
 * License: This file is licensed under the MIT License.
 *          See the LICENSE file for more details.
 */
#include <tuple>
#include <iostream>
#include <optional>
#include "result.h"
#include "minimax.h"
#include "options.h"
#include "tictactoe.h"


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

// game if multiplayer is chosen
void multiplayer() {
    TicTacToe game;
    clear();
    std::string banner = "Provide coordinate: {NUMBER}{LETTER}";
    while (true) {
        clear();
        std::cerr << banner << std::endl;
        std::cout << game.display() << std::endl;
        if (game.planeHasBeenFilled() || game.hasBeenWon()) {
            break;
        }
        std::cout << '\n' << "Its player '" << game.getCurrentPlayer() << "' turn" << std::endl;
        std::string selection = input("Coordinate: ");
        Result<std::tuple<int, int>, std::string> result = parse_input(selection);
        if (result.is_err()) {
            banner = result.unwrap_err();
            continue;
        }
        int row;
        int col;
        std::tie(row, col) = result.unwrap();
        {
            Result<TicTacToe, std::string> result = game.place(row, col);
            if (result.is_err()) {
                banner = result.unwrap_err();
                continue;
            }
            game = result.unwrap();
        }
    }
    if (game.hasBeenWon()) {
        std::cout << "'" << game.getPreviousPlayer() << "' player has won!" << std::endl;
    } else {
        std::cout << "It's a tie" << std::endl;
    }
}

// Game if soloplayer is chosen
void soloplayer() {
    TicTacToe game;
    clear();
    std::string banner = "Provide coordinate: {NUMBER}{LETTER}";
    while (true) {
        clear();
        std::cerr << banner << std::endl;
        std::cout << game.display() << std::endl;
        if (game.planeHasBeenFilled() || game.hasBeenWon()) {
            break;
        }
        char current_player = game.getCurrentPlayer();
        std::cout << '\n' << "Its player '" << current_player << "' turn" << std::endl;
        if (current_player == 'O') { // O is human player
            std::string selection = input("Coordinate: ");
            Result<std::tuple<int, int>, std::string> result = parse_input(selection);
            if (result.is_err()) {
                banner = result.unwrap_err();
                continue;
            }
            int row;
            int col;
            std::tie(row, col) = result.unwrap();
            {
                Result<TicTacToe, std::string> result = game.place(row, col);
                if (result.is_err()) {
                    banner = result.unwrap_err();
                    continue;
                }
                game = result.unwrap();
            }
        } else { // ai player, which is X
            int _;
            std::optional<std::tuple<int, int>> best_move;
            std::tie(_, best_move) = minimax(game, 9, true);
            if (!best_move.has_value()) {
                continue;
            }
            int row;
            int col;
            std::tie(row, col) = best_move.value();
            TicTacToe updated_game_state = game.place(row, col).unwrap();
            game = updated_game_state;
        }
    }
    if (game.hasBeenWon()) {
        std::cout << "'" << game.getPreviousPlayer() << "' player has won!" << std::endl;
    } else {
        std::cout << "It's a tie" << std::endl;
    }
}

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

int main() {
    std::string game_mode = getGameMode();
    if (game_mode == "multiplayer") {
        multiplayer();
    } else if (game_mode == "soloplayer") {
        soloplayer();
    }
    return 0;
}
