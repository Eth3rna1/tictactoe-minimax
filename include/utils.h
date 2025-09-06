// Filename: utils.h
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 2/22/2025
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

#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include "result.h"
#include "options.h"

// Clears the terminal screen
void clear();

// Outputs the prompt before receiving user input
std::string input(const std::string& prompt);

// Outputs a prompt that needs boolean input before returning such input as true or false
bool confirmPrompt(const std::string& prompt, bool default_bool);

// After making a selection on coordinate regarding the Tic Tac Toe game,
// the function will translate the input into numerical x and y coordiantes
Result<std::tuple<int, int>, std::string> parseInput(const std::string& response);

// Outputs a list of options for the client to choose from
// and returns the choice of the client regarding their input
std::string getGameMode();

#endif
