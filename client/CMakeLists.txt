cmake_minimum_required(VERSION 3.10)
project(StockClient)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Find all .cpp files in src/ and subdirectories
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Include subdirectories in include/
file(GLOB INCLUDE_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/*)

foreach(dir ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/include/${dir})
        include_directories(${CMAKE_SOURCE_DIR}/include/${dir})
    endif()
endforeach()

include_directories(
    include/
    include/*
    ../common/include/
    ${CMAKE_SOURCE_DIR}/client/imgui
    ${CMAKE_SOURCE_DIR}/client/imgui/backends
)

# Define the ImGui source files
set(IMGUI_SRC
    ${CMAKE_SOURCE_DIR}/client/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/client/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/client/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/client/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/client/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/client/imgui/backends/imgui_impl_sdl2.cpp
    ${CMAKE_SOURCE_DIR}/client/imgui/backends/imgui_impl_opengl3.cpp
)

# Define the executable
add_executable(client ${SRC_FILES} ${IMGUI_SRC})

# Link the common library
target_link_libraries(client PRIVATE common)

# Find and link OpenGL and SDL2
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

target_link_libraries(client PRIVATE ${SDL2_LIBRARIES} OpenGL::GL)

# Ensure the compiler searches the include directory
target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/include)
