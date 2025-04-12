#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <csignal>
#include <atomic>
#include <iostream>

#include "Message.hpp"
#include "Constants.hpp"

// A global atomic flag to signal shutdown
std::atomic<bool> shouldExit(false);

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "\nExiting...\n";
        shouldExit = true;
    }
}

#endif // SIGNALS_HPP
