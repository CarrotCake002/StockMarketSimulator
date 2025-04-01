cmake_minimum_required(VERSION 3.10)
project(CommonTests)

enable_testing()

find_package(GTest REQUIRED)

# Add the test executable
add_executable(common_tests utils_test.cpp)

# Link the test executable with GTest::Main, pthread, and the common library
target_link_libraries(common_tests PRIVATE GTest::Main pthread common)

# Ensure the test executable can find the common library's headers
target_include_directories(common_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Register the test with CTest
add_test(NAME CommonTests COMMAND common_tests)