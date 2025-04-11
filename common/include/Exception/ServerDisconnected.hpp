#ifndef SERVER_DISCONNECTED_EXCEPTION_HPP
#define SERVER_DISCONNECTED_EXCEPTION_HPP

#include <exception>
#include <string>

#include "Constants.hpp"

namespace Exception {

    class ServerDisconnected : public std::exception {
    public:
        explicit ServerDisconnected(int fd) : fd(fd) {};

        const char* what() const noexcept override {
            std::string message = "Client with fd " + std::to_string(fd) + " requested a server shutdown";
            return message.c_str();
        }

    private:
        int fd;
    };

}

#endif // SERVER_DISCONNECTED_EXCEPTION_HPP