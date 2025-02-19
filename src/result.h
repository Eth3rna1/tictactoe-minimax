/*
    Making a similar API to Rust's Result
*/
#include <iostream>
#include <variant>
#include <typeinfo>
#include <cstdlib>

template <typename V, typename E>
class Result {
    std::variant<V, E> __result;

public:
    Result(const V& val) : __result(val) {}  // Success case
    Result(const E& err) : __result(err) {} // Error case

    bool is_ok() const {
        return std::holds_alternative<V>(this->__result);
    }

    bool is_err() const {
        return std::holds_alternative<E>(this->__result);
    }

    V unwrap() const {
        if (this->is_ok()) {
            return std::get<V>(this->__result);
        }
        std::cout << "Error: Unwrapping a failed result!" << std::endl;
        exit(1); // Exit the program on error (like panicking in Rust)
    }

        // Retrieve the error value
    E unwrap_err() const {
        if (this->is_err()) {
            return std::get<E>(this->__result);
        }
        std::cout << "Error: Unwrapping a successful result!" << std::endl;
        exit(1); // Exit the program on error
    }
};
