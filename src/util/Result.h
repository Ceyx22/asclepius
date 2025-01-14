//
// Created by ceyx on 1/11/25.
//

#ifndef RESULT_H
#define RESULT_H
#include <string>
#include <variant>

template<typename T, typename E>
class Result {
public:
    // Constructors for success and error
    static Result<T, E> Ok(T value) { return Result(std::move(value)); }
    static Result<T, E> Err(E error) { return Result(std::move(error)); }

    // Check if the result is a success
    [[nodiscard]] bool isOk() const { return std::holds_alternative<T>(result); }

    // Access the value or error
    T &unwrap() { return std::get<T>(result); }
    const T &unwrap() const { return std::get<T>(result); }
    E &unwrapErr() { return std::get<E>(result); }
    const E &unwrapErr() const { return std::get<E>(result); }

private:
    std::variant<T, E> result;

    // Private constructors
    explicit Result(T value) : result(std::move(value)) {
    }

    explicit Result(E error) : result(std::move(error)) {
    }
};
#endif //RESULT_H
