# RubiksCubeSolver

### Building on Linux:
1. `sudo apt install cmake libsdl2-dev g++`
2. Run from root, or set the working direcroey to the root folder in your IDE

### Building on Windows (Visual Studio):
1. Write the path to your SDL2 folder in CMakeLists.txt
2. If the project is not built with a Visual Studio generator, the working directory needs to be changed. change your launch.vs.json like this:
```
"project": "CMakeLists.txt",
"projectTarget": "RubiksCubeSolver.exe",
"name": "RubiksCubeSolver.exe",
"currentDir": "path\\to\\RubiksCubeSolver" // where RubiksCubeSolver is the root folder of the project
```
   

**Make sure that your compiler supports C++20**
