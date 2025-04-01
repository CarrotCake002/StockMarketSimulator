cmake_minimum_required(VERSION 3.10)
project(ServerTests)

enable_testing()

find_package(GTest REQUIRED)

# Find all .cpp files in the test server src directory
file(GLOB_RECURSE SERVER_SRC_FILES "src/*.cpp")

# Add the test executable
add_executable(server_tests server_tests.cpp ${SERVER_SRC_FILES})

# Link the test executable with GTest::Main, pthread, and the common library
target_link_libraries(server_tests PRIVATE GTest::Main pthread common)

# Ensure the test executable can find the server library's headers
target_include_directories(server_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Register the test with CTest
add_test(NAME ServerTest COMMAND server_tests)