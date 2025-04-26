#include "ServerManager.hpp"

std::atomic<bool> serverShutdown(false);

// Error handling
bool inputErrorHandling(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        return false;
    }
    if (std::stoi(av[1]) <= 0 || std::stoi(av[1]) > 65535) {
        std::cerr << ERROR_INVALID_PORT << std::endl;
        return false;
    }
    return true;
}

int main(int ac, char **av) {
    int port;

    if (!inputErrorHandling(ac, av))
        return 84;
    port = std::stoi(av[1]);

    try {
        ServerManager serverManager(port);
        serverManager.run();
    } catch (...) {
        return 84;
    }

    return 0;
}
