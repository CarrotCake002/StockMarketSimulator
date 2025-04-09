#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <string>

#include "Constants.hpp"
#include "Manager/MessageManager.hpp"

#define EXIT_COMMAND "exit"
#define HELP_COMMAND "help"

#define HELP_MESSAGE "Available commands: help, exit"

class Input {
public:
    virtual ~Input() = default;

    static bool checkHelp(const std::string& input) {
        return input == HELP_COMMAND ? true : false;
    }

    static bool checkExit(const std::string input) {
        return input == EXIT_COMMAND ? true : false;
    }

    static int parse(const std::string& input) {
        if (checkExit(input))
        return 0;
    }

    static void validate(const std::string& input) {
        // Example validation logic
        if (input.empty()) {
            throw std::invalid_argument(ERROR_INVALID_COMMAND);
        }
    }
};

#endif // INPUT_HPP