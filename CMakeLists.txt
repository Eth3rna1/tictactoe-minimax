cmake_minimum_required(VERSION 3.10)
project(tictactoe-minimax LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/utils.cpp
    src/options.cpp
    src/tictactoe.cpp
    src/minimax.cpp
)

add_executable(tictactoe ${SOURCES})

# Optional: Show warnings
if (MSVC)
    target_compile_options(tictactoe PRIVATE /W4 /permissive-)
else()
    target_compile_options(tictactoe PRIVATE -Wall -Wextra -pedantic)
endif()
