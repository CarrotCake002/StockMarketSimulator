## Continuous Integration and Deployment (CI/CD)

This project includes a CI/CD pipeline implemented using GitHub Actions. The pipeline automates the build, test, and deployment processes to ensure code quality and streamline development. Key features of the CI/CD setup include:

- **Automated Builds**: Every push or pull request triggers a build process to verify the integrity of the codebase.
- **Unit Testing**: Tests from the `client/tests`, `server/tests`, and `common/tests` folders are executed to ensure functionality remains intact.
- **Cross-Platform Support**: The pipeline is configured to run on multiple operating systems (e.g., Linux, macOS, Windows) to ensure compatibility.
- **Deployment**: Artifacts from successful builds are stored for deployment or further testing.

The CI/CD configuration is defined in the `.github/workflows` directory, making it easy to modify or extend as needed.

## Project Structure

The project is organized as follows:

- **client/**: Contains the source code (`src/`) and tests (`tests/`) for the client-side application.
- **server/**: Contains the source code (`src/`) and tests (`tests/`) for the server-side application.
- **common/**: Includes a shared library with common functionality used by both the client and server. This folder also contains its own `src/` and `tests/` directories.

## Build System

This is a C++ project that uses CMake as its build system. CMake simplifies the process of building and managing dependencies across the client, server, and common components. Each subdirectory is configured with its own CMakeLists.txt file, which is integrated into the top-level CMake configuration.

## Testing

Unit tests are implemented for all components of the project. The testing framework is integrated into the CI/CD pipeline to ensure that all tests are executed automatically during the build process. Tests are located in the `tests/` directories within the `client/`, `server/`, and `common/` folders.

## Getting Started

To build and run the project, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/CarrotCake002/StockMarketSimulator
    cd StockMarketSimulator
    ```

2. Create a build directory and configure the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3. Build the project:
    ```bash
    cmake --build .
    ```

4. Run the tests:
    ```bash
    ctest
    ```

5. Execute the client and server applications:
    ```bash
    ./server/server <port>
    ./client/client <IP> <port>
    ```
