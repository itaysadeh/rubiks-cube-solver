# RubiksCubeSolver

### Building on Linux
1. `sudo apt install cmake libsdl2-dev g++`
2. Run from the root project folder, or set the working direcroey to the root folder in your IDE

### Building on Windows
1. Write the path to your SDL2 folder in CMakeLists.txt
2. If the project is not built with a Visual Studio generator (like ninja), the working directory needs to be changed. 
   For Visual studio: change your launch.vs.json accordingly:
"project": "CMakeLists.txt",
"projectTarget": "RubiksCubeSolver.exe",
"name": "RubiksCubeSolver.exe",
"currentDir": "path\\to\\RubiksCubeSolver" (RubiksCubeSolver is the root project folder)
```
   

**Make sure that your compiler supports C++20**
