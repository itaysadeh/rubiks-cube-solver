# RubiksCubeSolver
Rubik's Cube solver written in C++

### Building on Linux:
1. `sudo apt install cmake libsdl2-dev g++`

### Building on Windows (Visual Studio):
1. Write the path to your SDL2 folder in CMakeLists.txt
2. To make sure the working directory is set to root (for opening files), set launch.vs.json this way:
        ```
        "project": "CMakeLists.txt",
        "projectTarget": "RubiksCubeSolver.exe",
        "name": "RubiksCubeSolver.exe",
        "currentDir": "path\\to\\RubiksCubeSolver"
        ```
   Otherwise, change the path in Database.cpp to match your working directory

**Make sure that your compiler supports C++20**
