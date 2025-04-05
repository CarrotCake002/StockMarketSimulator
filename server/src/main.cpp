#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        return 1;
    }

    // Define address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen for a connection
    listen(server_fd, 1);
    std::cout << "Waiting for a connection on port " << PORT << "...\n";

    // Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        return 1;
    }

    std::string hello = "Hello from server";
    send(new_socket, hello.c_str(), hello.length(), 0);
    std::cout << "Message sent to client\n";

    close(new_socket);
    close(server_fd);
    return 0;
}
