cmake_minimum_required(VERSION 3.10)
project(ServerClientProject)

# Add subdirectories for the main components
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)


# Enable testing
enable_testing()

# Add a custom target for building tests
add_custom_target(tests)

# Add subdirectories for tests only when the "tests" target is invoked
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR AND TARGET tests)
    add_subdirectory(common/tests)
    add_dependencies(tests common_tests)

    add_subdirectory(server/tests)
    add_dependencies(tests server_tests)

    add_subdirectory(client/tests)
    add_dependencies(tests client_tests)
endif()