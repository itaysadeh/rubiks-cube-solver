# rubiks-cube-solver

Set the working directory to the root project folder or run the executable from there (or the lookup tables will be regenerated every time)

### Building on Linux
1. `sudo apt install cmake libsdl2-dev g++`

### Building on Windows
1. Write the path to your SDL2 folder in CMakeLists.txt
2. To set the working directory to the root project folder in Visual Studio, change launch.vs.json accordingly:
```
"project": "CMakeLists.txt",
"projectTarget": "RubiksCubeSolver.exe",
"name": "RubiksCubeSolver.exe",
"currentDir": "path\\to\\root"
```
   

**Make sure that your compiler supports C++20**
