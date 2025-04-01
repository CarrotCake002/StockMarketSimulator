file(GLOB_RECURSE COM_FILES "src/*.cpp")

# Define the common library
add_library(common STATIC ${COM_FILES})

# Add include directories for the common library
target_include_directories(common PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include the current directory so other targets can find the headers
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
