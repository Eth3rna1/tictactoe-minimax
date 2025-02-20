// A tic tac toe game with the mini-max algorithm

#include <iostream>
#include "minimax.h"
#include "options.h"
#include <stdexcept>

constexpr void clear() {
    std::cout << "\x1B[2J\x1B[1;1H";
}

std::string input(auto& prompt) {
    std::cout << prompt;
    std::string response;
    std::getline(std::cin, response);
    return response;
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
    std::string banner = "Provide coordinate with {NUMBER}{LETTER}";
    /*while (!game.planeHasBeenFilled() || !game.hasBeenWon()) {*/
    while (true) {
        clear();
        std::cerr << banner << std::endl;
        std::cout << game.display() << std::endl;
        if (game.planeHasBeenFilled() || game.hasBeenWon()) {
            break;
        }
        std::cout << '\n' << "Its player '" << game.getCurrentPlayer() << "' turn" << std::endl;
        std::string selection = input("Coordinate: ");
        auto result = parse_input(selection);
        if (result.is_err()) {
            banner = result.unwrap_err();
            continue;
        }
        int row;
        int col;
        std::tie(row, col) = result.unwrap();
        {
            auto result = game.place(row, col);
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

void soloplayer() {
    TicTacToe game;
    clear();
    std::string banner = "Provide coordinate with {NUMBER}{LETTER}";
    /*while (!game.planeHasBeenFilled() || !game.hasBeenWon()) {*/
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
            auto result = parse_input(selection);
            if (result.is_err()) {
                /*std::cerr << '\r' << result.unwrap_err() << std::endl;*/
                banner = result.unwrap_err();
                continue;
            }
            int row;
            int col;
            // parsed the human input
            std::tie(row, col) = result.unwrap();
            {
                auto result = game.place(row, col);
                if (result.is_err()) {
                    /*std::cerr << '\r' << result.unwrap_err() << std::endl;*/
                    banner = result.unwrap_err();
                    continue;
                }
                game = result.unwrap();
            }
        } else { // ai player, which is X
            int _;
            std::optional<COORDINATE> best_move;
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
        /*std::cout << "Provide coordinate with {NUMBER}{LETTER}.\n";*/
        /*std::cout << game.display() << std::endl;*/
    }
    if (game.hasBeenWon()) {
        std::cout << "'" << game.getPreviousPlayer() << "' player has won!" << std::endl;
    } else {
        std::cout << "It's a tie" << std::endl;
    }
}

std::string getGameMode() {
    std::vector<std::string> opts = {"soloplayer", "multiplayer"};
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
