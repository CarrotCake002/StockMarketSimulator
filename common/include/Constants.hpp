#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>

// Server Info
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

// IP Address
#define IP_FORMAT "0123456789."

// Port Range
#define PORT_MIN 0
#define PORT_MAX 65535

// Server Greeting
#define SERVER_GREETING "Hello from server"
#define SERVER_DISCONNECT_MESSAGE "You disconnected from server."
#define SERVER_ERROR_MESSAGE "Error processing command"

// Server Commands
#define SERVER_HELP_COMMAND "help"
#define SERVER_EXIT_COMMAND "exit"
#define SERVER_HELP_MESSAGE "Available commands: help, exit"
#define SERVER_EMPTY_COMMAND ""

// Socket Constants
#define SOCKET_ERROR -1
#define SOCKET_BUFFER_SIZE 1024

// Connection Errors
#define ERROR_SOCKET_CREATION "Socket creation failed"
#define ERROR_BINDING "Binding failed"
#define ERROR_LISTENING "Listening failed"
#define ERROR_ACCEPTING "Accepting connection failed"
#define ERROR_CONNECTING "Connecting to server failed"
#define ERROR_INVALID_SOCKET "Invalid socket descriptor"
#define ERROR_CONNECTION_CLOSED "Connection closed"
#define ERROR_READING_SOCKET "Reading from socket failed"

// Arguemnt Errors
#define ERROR_INVALID_ARGUMENT "Invalid argument"
#define ERROR_INVALID_IP "Invalid IP address format"
#define ERROR_INVALID_PORT "Port must be between 1 and 65535"

// Message Errors
#define ERROR_SENDING "Sending message failed"
#define ERROR_RECEIVING "Receiving message failed"

// Command Errors
#define ERROR_UNKNOWN_COMMAND "Unknown command"
#define ERROR_INVALID_COMMAND "Invalid command"
#define ERROR_EMPTY_COMMAND "Command cannot be empty"
#define ERROR_PROCESSING_COMMAND "Error processing command"

// Thread errors
#define ERROR_THREAD_CREATION "Thread creation failed"
#define ERROR_THREAD_DETACH "Thread detach failed"

// Info Messages
#define INFO_CLIENT_CONNECTED "Client connected"
#define INFO_CLIENT_DISCONNECTED "Client disconnected"
#define INFO_CLIENT_DISCONNECTED_FD "Client with fd {} disconnected."
#define INFO_CLIENT_CONNECTED_FD "Client connected with fd: "
#define INFO_WAITING_FOR_CONNECTION "Waiting for a connection on port "
#define INFO_WAITING_NEW_CONNECTION "Waiting for a new connection..."
#define INFO_EXITING_CLIENT "Exiting client."
#define INFO_CONNECTED_TO_SERVER "Connected to server at "

// Other Errors
#define ERROR_UNEXPECTED "An unexpected error occurred"
#define ERROR_RUNTIME "Runtime error occurred"
#define ERROR "Error: "
#define RUNTIME_ERROR "Runtime Error: "

// Other Messages
#define INPUT_PROMPT "> "
#define RESPONSE "Response: "

#endif // CONSTANTS_HPP