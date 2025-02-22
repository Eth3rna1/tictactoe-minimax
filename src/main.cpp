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
 * Last Modified: 2/22/2025
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
 * g++ src/main.cpp -o tictactoe.exe
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
#include "../include/utils.h"
#include "../include/result.h"
#include "../include/minimax.h"
#include "../include/options.h"
#include "../include/tictactoe.h"

constexpr int MAX_MINIMAX_DEPTH = 9;
constexpr bool X_IS_MAXIMIZER = true;
constexpr bool DEFAULT_REPLAY_RESPONSE = false;

// game if multiplayer is chosen
void multiPlayer() {
    TicTacToe game;
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
        Result<std::tuple<int, int>, std::string> input_result = parseInput(selection);
        if (input_result.isErr()) {
            banner = input_result.unwrapErr();
            continue;
        }
        int row;
        int col;
        std::tie(row, col) = input_result.unwrap();
        Result<TicTacToe, std::string> result = game.place(row, col);
        if (result.isErr()) {
            banner = result.unwrapErr();
            continue;
        }
        game = result.unwrap();
    }
    if (game.hasBeenWon()) {
        std::cout << "'" << game.getPreviousPlayer() << "' player has won!" << std::endl;
    } else {
        std::cout << "It's a tie" << std::endl;
    }
}

// Game if soloplayer is chosen
void soloPlayer() {
    TicTacToe game;
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
            Result<std::tuple<int, int>, std::string> input_result = parseInput(selection);
            if (input_result.isErr()) {
                banner = input_result.unwrapErr();
                continue;
            }
            int row;
            int col;
            std::tie(row, col) = input_result.unwrap();
            Result<TicTacToe, std::string> result = game.place(row, col);
            if (result.isErr()) {
                banner = result.unwrapErr();
                continue;
            }
            game = result.unwrap();
        } else { // ai player, which is X
            int _;
            std::optional<std::tuple<int, int>> best_move;
            std::tie(_, best_move) = minimax(game, MAX_MINIMAX_DEPTH, X_IS_MAXIMIZER);
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

int main() {
    while (true) {
        std::string game_mode = getGameMode();
        if (game_mode == "multiplayer") {
            multiPlayer();
        } else if (game_mode == "soloplayer") {
            soloPlayer();
        }
        if (!confirmPrompt("Replay?", DEFAULT_REPLAY_RESPONSE)) {
            break;
        }
    }
    return 0;
}
