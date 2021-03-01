# RubiksCubeSolver
Rubik's Cube solver written in C++

### For building on Linux:
1. `sudo apt install cmake libsdl2-dev g++`

### For building on Windows (Visual Studio):
1. Write the path to your SDL2 folder in CMakeLists.txt (set(SDL2_DIR "path/to/sdl2/folder"))
2. If building through CMake GUI, make sure to select RubiksCubeSolver as the startup project
3. Add the required dll files from your SDL2 folder to where Visual Studio outputs the .exe files

**Make sure that your compiler supports C++20**
