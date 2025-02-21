// Filename: result.h
//
// Author: Gabriel Mendieta Hernandez <gmendieta4109@gmail.com>
//
// Date: 2/20/2025
//
// Description: This file contains the Rust class; assimilates Rust's API.
//
// License: This file is licensed under the MIT License.
//          See the LICENSE file for more details.
//
// Dependencies:
//    System Headers: 
//        - <variant>    // Functionality to store a success value and an error value
//        - <stdexcept>  // Used to throw a runtime error when unwrapping the wrong variant
#ifndef RESULT_H
#define RESULT_H

#include <variant>
#include <stdexcept>

// Assimilates Rust's `Result` API, which contains the success case
// and stores the error case within a value instead of playing throw and catch
template <typename V, typename E>
class Result {
    std::variant<V, E> m_result;

public:
    Result(const V& val) : m_result(val) {}  // Success case
    Result(const E& err) : m_result(err) {} // Error case

    // checks if the value is the success case
    bool isOk() const {
        return std::holds_alternative<V>(this->m_result);
    }

    // checks if the value is the error case
    bool isErr() const {
        return std::holds_alternative<E>(this->m_result);
    }

    // returns success case's value
    V unwrap() const {
        if (this->isOk()) {
            return std::get<V>(this->m_result);
        }
        throw std::runtime_error("Error: Unwrapping a failed result!");
        exit(1); // Exit the program on error (like panicking in Rust)
    }

    // returns the error value
    E unwrapErr() const {
        if (this->isErr()) {
            return std::get<E>(this->m_result);
        }
        throw std::runtime_error("Error: Unwrapping a successful result!");
        exit(1); // Exit the program on error
    }
};

#endif
