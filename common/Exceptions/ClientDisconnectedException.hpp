#ifndef CLIENT_DISCONNECTED_EXCEPTION_HPP
#define CLIENT_DISCONNECTED_EXCEPTION_HPP

#include <exception>
#include <string>

#include "Constants.hpp"

class ClientDisconnectedException : public std::exception {
public:
    explicit ClientDisconnectedException(const std::string& message)
        : message_(message) {}

    const char* what() const noexcept override {
        return INFO_CLIENT_DISCONNECTED;
    }

private:
    std::string message_;
};

#endif // CLIENT_DISCONNECTED_EXCEPTION_HPP