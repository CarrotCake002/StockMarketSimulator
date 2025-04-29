#include "ServerManager.hpp"

std::atomic<bool> serverShutdown(false);

// Error handling
bool inputErrorHandling(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Usage: " << av[0] << " <port> <speedMultiplier>" << std::endl;
        return false;
    }
    if (std::stoi(av[1]) <= 0 || std::stoi(av[1]) > 65535) {
        std::cerr << ERROR_INVALID_PORT << std::endl;
        return false;
    }
    if (std::stod(av[2]) <= 0) {
        std::cerr << ERROR_INVALID_SPEED_MULTIPLIER << std::endl;
        return false;
    }
    return true;
}

int main(int ac, char **av) {
    int port;
    double speedMultiplier;

    if (!inputErrorHandling(ac, av))
        return 84;
    port = std::stoi(av[1]);
    speedMultiplier = std::stod(av[2]);

    try {
        srand(static_cast<unsigned int>(time(nullptr)));
        ServerManager serverManager(port, speedMultiplier);
        serverManager.run();
    } catch (...) {
        return 84;
    }

    return 0;
}
