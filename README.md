# RubiksCubeSolver
Rubik's Cube solver written in C++

### Building on Linux:
1. `sudo apt install cmake libsdl2-dev g++`

### Building on Windows (Visual Studio):
1. Write the path to your SDL2 folder in CMakeLists.txt
2. If the project is not built with a Visual Studio generator, set launch.vs.json this way:
```
"project": "CMakeLists.txt",
"projectTarget": "RubiksCubeSolver.exe",
"name": "RubiksCubeSolver.exe",
"currentDir": "path\\to\\RubiksCubeSolver"
```
   To make the working directory /root (for opening database files).
   Otherwise, change the path in Database.cpp to match your working directory

**Make sure that your compiler supports C++20**
