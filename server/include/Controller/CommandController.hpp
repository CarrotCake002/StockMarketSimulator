#ifndef COMMAND_CONTROLLER_HPP
#define COMMAND_CONTROLLER_HPP

#include "Constants.hpp"
#include "Controller/SocketController.hpp"
#include "Exception/ServerDisconnected.hpp"
#include "Controller/ServerMessageController.hpp"
#include "Atomic.hpp"
#include "Stocks/StockManager.hpp"

#include <vector>
#include <sstream>

enum class Command {
    HELP,
    EXIT,
    LIST,
    SHUTDOWN,
    BUY,
    SELL
};

class CommandController {
public:
    CommandController(int client_socket, StockManager *StockManager) : client_socket(client_socket), stockManager(StockManager) {}
    ~CommandController() = default;

    std::vector<std::string> splitCommand(const std::string& command) {
        std::vector<std::string> arguments;
        std::istringstream iss(command);
        std::string token;

        while (iss >> token) {
            arguments.push_back(token);
        }
        return arguments;
    }

    Command parseCommand(const std::string& command) {
        std::cout << "\"" << command << "\" received from client with fd " << client_socket << std::endl;
        if (command == "help") {
            return Command::HELP;
        } else if (command == "exit") {
            return Command::EXIT;
        } else if (command == "list") {
            return Command::LIST;
        } else if (command == "shutdown") {
            return Command::SHUTDOWN;
        } else if (command.find("buy") == 0) {
            return Command::BUY;
        } else if (command.find("sell") == 0) {
            return Command::SELL;
        } else {
            throw std::invalid_argument("Unknown command");
        }
    }

    void executeHelp(void) {
        try {
            ServerMessage::sendMessage(client_socket, HELP_MESSAGE);
        } catch (const std::runtime_error& e) {
            throw e;
        }
        std::cout << "Help message sent to client with fd " << client_socket << std::endl;
    }

    void executeExit(void) {
        try {
            ServerMessage::sendMessage(client_socket, INFO_CLIENT_DISCONNECTED);
            std::cout << "Client with fd " << client_socket << " disconnected." << std::endl;
        } catch (const std::runtime_error& e) {
            throw e;
        }
    }

    void executeShutdown(void) {
        try {
            ServerMessage::sendMessage(client_socket, INFO_SERVER_SHUTDOWN);
            std::cout << INFO_SERVER_SHUTDOWN << std::endl;
            serverShutdown = true;
        } catch (const std::runtime_error& e) {
            throw e;
        }
    }

    void executeList(void) {
        try {
            stockManager->displayStockInfo(client_socket);
        } catch (const std::runtime_error& e) {
            throw e;
        }
    }

    void executeBuy(const std::string& command) {
        std::vector<std::string> arguments = splitCommand(command);
        StockType stockType;

        try {
            if (arguments.size() < 3) {
                throw std::invalid_argument(ERROR_INVALID_ARGUMENT);
            }
            stockType = stockManager->parseStockType(arguments[1]);
            stockManager->buyStock(stockType, std::stoi(arguments[2]));
        } catch (const std::invalid_argument& e) {
            throw e;
        }
        Message::sendMessage(client_socket, "You bought " + std::to_string(std::stoi(arguments[2])) + " shares of " + arguments[1]);
    }

    void executeSell(const std::string& command) {
        std::vector<std::string> arguments = splitCommand(command);
        StockType stockType;
    
        try {
            if (arguments.size() < 3) {
                throw std::invalid_argument(ERROR_INVALID_ARGUMENT);
            }
            stockType = stockManager->parseStockType(arguments[1]);
            stockManager->sellStock(stockType, std::stoi(arguments[2]));
        } catch (const std::invalid_argument& e) {
            throw e;
        }
        Message::sendMessage(client_socket, "You sold " + std::to_string(std::stoi(arguments[2])) + " shares of " + arguments[1]);
    }

    void executeCommand(Command cmd, const std::string& command) {
        try {
            if (cmd == Command::HELP) {
                executeHelp();
            } else if (cmd == Command::EXIT) {
                executeExit();
            } else if (cmd == Command::LIST) {
                executeList();
            } else if (cmd == Command::SHUTDOWN) {
                executeShutdown();
            } else if (cmd == Command::BUY) {
                executeBuy(command);
            } else if (cmd == Command::SELL) {
                executeSell(command);
            }
        } catch (const std::invalid_argument& e) {
            throw e;
        } catch (const std::exception& e) {
            throw e;
        }
    }

private:
    int client_socket;
    StockManager *stockManager;
};

#endif // COMMAND_CONTROLLER_HPP