#include <csignal>
#include <atomic>
#include <iostream>

#include "Manager/MessageManager.hpp"
#include "Constants.hpp"

// A global atomic flag to signal shutdown
std::atomic<bool> shouldExit(false);

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "\nExiting...\n";
        shouldExit = true;
    }
}
