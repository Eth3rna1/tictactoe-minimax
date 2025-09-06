// Filename: options.cpp
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 9/6/2025
//
// Description: Implementation file for the Option class; used for optional selection.
//
// License: This file is licensed under the MIT License.
//          See the LICENSE file for more details.
//
// Dependencies:
//    System Headers: 
//        - <optional>       // Used for type safety, the function "COULD" return a coordinate
//        - <vector>         // Didn't want to deal with a static array when working with the constructor
//        - <unordered_map>  // Contains optional values corresponding with their index in the Options class
#include <vector>
#include <string>
#include <optional>
#include <unordered_map>
#include "../include/options.h"


Options::Options(const std::vector<std::string>& values) {
    for (int i=0; i < values.size(); ++i) {
        m_values[std::to_string(i + 1)] = values[i];
    }
}

// Returns a UI for the user to
// have all the clients options on a list
std::string Options::display() const {
    std::string buffer = "";
    int size = m_values.size();
    for (int i=0; i < size; ++i) {
        std::string str_index = std::to_string(i + 1);
        buffer += str_index + ".) " + m_values.at(str_index);
        if (i < size - 1) {
            buffer += '\n';
        }
    }
    return buffer;
}

// Evaluates user input `v` and matches the keys first,
// returning the value corresponding to the key, if not, checks
// for the values, if values match, returns such value
std::optional<std::string> Options::eval(std::string v) {
    for (const auto& pair : m_values) {
        if (pair.first == v) {
            return pair.second;
        } else if (pair.second == v) {
            return v;
        }
    }
    return std::nullopt;
}

