# RubiksCubeSolver
Rubik's Cube solver written in C++

For building on Linux:
1. sudo apt install cmake libsdl2-dev g++
2. SDL2 folder is not needed, and can be deleted from the project

For building on Windows (Visual Studio):
1. If building through CMake, make sure to select RubiksCubeSolver as the startup project
2. Copy dll files from SDL/lib/ to the output folder where VS generates .exe files
3. If you have SDL2 installed somewhere else already, change the MakeFIleLists as described

Make sure that your compiler supports C++20
