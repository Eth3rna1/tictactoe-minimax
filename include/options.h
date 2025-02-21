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

#include <optional>
#include <vector>
#include <unordered_map>

// A class that works with the UI, listing all available
// options and deals with user selection to evaluate list selection
class Options {
    std::unordered_map<std::string, std::string> __values;

public:
    Options(std::vector<std::string>& values) {
        for (int i=0; i < values.size(); ++i) {
            __values[std::to_string(i + 1)] = values[i];
        }
    }

    // Returns a UI for the user to
    // have all the clients options on a list
    std::string display() const {
        std::string buffer = "";
        int size = __values.size();
        for (int i=0; i < size; ++i) {
            std::string str_index = std::to_string(i + 1);
            buffer += str_index + ".) " + __values.at(str_index);
            if (i < size - 1) {
                buffer += '\n';
            }
        }
        return buffer;
    }

    // Evaluates user input `v` and matches the keys first,
    // returning the value corresponding to the key, if not, checks
    // for the values, if values match, returns such value
    std::optional<std::string> eval(std::string v) {
        for (const auto& pair : __values) {
            if (pair.first == v) {
                return pair.second;
            } else if (pair.second == v) {
                return v;
            }
        }
        return std::nullopt;
    }
};

#endif
