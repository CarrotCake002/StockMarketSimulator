# StockMarketSimulator

A multithreaded TCP-based stock market simulator designed to explore network programming and concurrency.  
This project allows users to buy and sell stocks that evolve randomly over time, aiming to maximize profits.  
**Note**: The stock price evolution is randomized and not based on real-world data.

## 🧠 Project Goals

- Rediscover and practice TCP socket programming.
- Implement multithreaded client-server architecture.
- Simulate a dynamic stock market environment.
- Facilitate buying and selling of stocks with evolving prices.

## 🏗️ Architecture Overview

The project is structured into three main components:

- **Client**: Handles user interactions and communicates with the server.
- **Server**: Manages stock data, client connections, and processes transactions.
- **Common**: Contains shared resources, such as data models and utility functions.

## 🚀 Getting Started

### Prerequisites

- C++ compiler supporting C++17 or later.
- CMake 3.10 or higher.

### Building the Project

1. Clone the repository:

   ```bash
   git clone https://github.com/CarrotCake002/StockMarketSimulator.git
   cd StockMarketSimulator
   ```

2. Create a build directory and navigate into it:

   ```bash
   mkdir build
   cd build
   ```

3. Generate build files with CMake:

   ```bash
   cmake ..
   ```

4. Build the project:

   ```bash
   cmake --build .
   ```

### Running the Application

1. Start the server:

   ```bash
   ./server/StockMarketServer
   ```

2. In a new terminal, start the client:

   ```bash
   ./client/StockMarketClient
   ```

The client will connect to the server, allowing you to interact with the simulated stock market.

## ⚙️ Features

- Real-time stock price updates with randomized fluctuations.
- Ability to buy and sell stocks through the client interface.
- Multithreaded server handling multiple client connections concurrently.
- Clean separation of concerns with modular codebase.

## 🧪 Testing

The project includes unit tests for various components. To run the tests:

1. Navigate to the build directory:

   ```bash
   cd build
   ```

2. Run the tests using CTest:

   ```bash
   ctest
   ```

Ensure that all tests pass to verify the integrity of the application.

## 📁 Project Structure

```
StockMarketSimulator/
├── client/            # Client-side application code
├── server/            # Server-side application code
├── common/            # Shared resources and utilities
├── .github/workflows/ # CI/CD configurations
├── CMakeLists.txt     # Build configuration
└── README.md          # Project documentation
```

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

