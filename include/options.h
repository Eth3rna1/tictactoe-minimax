// Filename: options.h
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 2/20/2025
//
// Description: This file contains the Option class; used for optional selection.
//
// License: This file is licensed under the MIT License.
//          See the LICENSE file for more details.
//
// Dependencies:
//    System Headers: 
//        - <optional>       // Used for type safety, the function "COULD" return a coordinate
//        - <vector>         // Didn't want to deal with a static array when working with the constructor
//        - <unordered_map>  // Contains optional values corresponding with their index in the Options class
#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include <string>
#include <optional>
#include <unordered_map>

// A class that works with the UI, listing all available
// options and deals with user selection to evaluate list selection
class Options {
    std::unordered_map<std::string, std::string> m_values;

public:
    Options(const std::vector<std::string>& values);

    // Returns a UI for the user to
    // have all the clients options on a list
    std::string display() const;

    // Evaluates user input `v` and matches the keys first,
    // returning the value corresponding to the key, if not, checks
    // for the values, if values match, returns such value
    std::optional<std::string> eval(std::string v);
};

#endif
