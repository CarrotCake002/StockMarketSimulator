cmake_minimum_required(VERSION 3.10)
project(ClientTests)

enable_testing()

find_package(GTest REQUIRED)

# Find all .cpp files in the test client src directory
file(GLOB_RECURSE CLIENT_SRC_FILES "src/*.cpp")

# Add the test executable
add_executable(client_tests client_tests.cpp ${CLIENT_SRC_FILES})

# Link the test executable with GTest::Main, pthread, and the common library
target_link_libraries(client_tests PRIVATE GTest::Main pthread common)

# Ensure the test executable can find the client headers
target_include_directories(client_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Register the test with CTest
add_test(NAME ClientTest COMMAND client_tests)