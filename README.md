# Tic-Tac-Toe With Minimax

## About
A terminal-based TicTacToe game in C++, implementing the **minimax** artificial intelligence algorithm. An algorithm that allows for self play by either trying to maximize or minimize the game score.
> More about the [minimax algorithm here](https://en.wikipedia.org/wiki/Minimax)

## Getting Started
* Clone the Repo
```console
git clone https://github.com/Eth3rna1/tictactoe-minimax.git
```
* Change directory into the project
```console
cd tictactoe-minimax
```

## Installation

### Prerequisites

- [CMake](https://cmake.org/download/) (version 3.10 or higher)
- A C++17-compatible compiler (e.g., MinGW-w64 for Windows)
- (Optional) [Ninja](https://ninja-build.org/) or MinGW Makefiles for faster builds

### Building on Windows

1. **Clone the repository:**
   ```console
   git clone https://github.com/yourusername/tictactoe-minimax.git
   cd tictactoe-minimax
   ```

2. **Create a build directory and navigate into it:**
   ```console
   mkdir build
   cd build
   ```

3. **Generate build files with CMake:**
   - For MinGW:
     ```console
     cmake -G "MinGW Makefiles" ..
     ```
   - Or for Ninja (if installed):
     ```console
     cmake -G "Ninja" ..
     ```

4. **Build the project:**
   ```console
   cmake --build .
   ```

5. **Run the executable:**
   ```console
   ./tictactoe.exe
   ```

### Compiling Directly With G++

Include all implementation files in the compilation command.
```console
g++ src/minimax.cpp src/options.cpp src/tictactoe.cpp src/utils.cpp src/main.cpp -o tictactoe.exe
```

## Notes
* When playing, the UI should help with how to input a coordinate in the TicTacToe matrix. Just in case, coordinate format is `{number}{letter}`.
