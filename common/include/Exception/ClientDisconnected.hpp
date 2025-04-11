#ifndef CLIENT_DISCONNECTED_EXCEPTION_HPP
#define CLIENT_DISCONNECTED_EXCEPTION_HPP

#include <exception>
#include <string>

#include "Constants.hpp"

namespace Exception {

    class ClientDisconnected : public std::exception {
    public:
        explicit ClientDisconnected(int fd) : fd(fd) {};

        const char* what() const noexcept override {
            std::string message = "Client with fd " + std::to_string(fd) + " disconnected";
            return message.c_str();
        }

    private:
        int fd;
    };

}

#endif // CLIENT_DISCONNECTED_EXCEPTION_HPP