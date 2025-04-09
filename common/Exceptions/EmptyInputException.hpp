#ifndef EMPTY_INPUT_EXCEPTION_HPP
#define EMPTY_INPUT_EXCEPTION_HPP

#include <exception>
#include <string>

#include "Constants.hpp"

class EmptyInputException : public std::exception {
public:
    explicit EmptyInputException();

    const char* what() const noexcept override {
        return ERROR_EMPTY_COMMAND;
    }
};

#endif // EMPTY_INPUT_EXCEPTION_HPP