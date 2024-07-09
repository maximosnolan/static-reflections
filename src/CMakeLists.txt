cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all source and header files
file(GLOB LIB_SOURCES "*.cpp" "*.cc")
file(GLOB LIB_HEADERS "*.h" "*.hpp")

# Add library target
add_library(refl ${LIB_SOURCES} ${LIB_HEADERS})

# Include current source directory
target_include_directories(refl
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

