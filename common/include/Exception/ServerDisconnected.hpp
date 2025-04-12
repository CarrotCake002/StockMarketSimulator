#ifndef SERVER_DISCONNECTED_EXCEPTION_HPP
#define SERVER_DISCONNECTED_EXCEPTION_HPP

#include <exception>
#include <string>

#include "Constants.hpp"

namespace Exception {

    class ServerDisconnected : public std::exception {
    public:
        explicit ServerDisconnected(int fd) : fd(fd) {
            errorMessage = "Client with fd " + std::to_string(fd) + " requested a server shutdown";
        }

        const char* what() const noexcept override {
            return errorMessage.c_str();
        }

    private:
        int fd;
        std::string errorMessage;
    };

}

#endif // SERVER_DISCONNECTED_EXCEPTION_HPP