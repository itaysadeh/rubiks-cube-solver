# rubiks-cube-solver

## Input
- To apply moves (perform face twists) use: `U`p, `L`eft, `F`ront, `R`ight, `B`ack and `D`own.
  (For counter-clockwise hold `shift`, for 180-degree (half twist) hold `lctrl`)
- To scramble the cube use `S`.
- To solve the cube with [Thistlethwaite's algorithm](https://www.jaapsch.net/puzzles/thistle.htm) use `F1`

## Thistlethwaite's algorithm
[Thistlethwaite's algorithm](https://www.jaapsch.net/puzzles/thistle.htm) solves the cube in less than 52 moves.
The cube is split into 5 sub-groups: G0, G1, G2, G3 and G4:
G0 is any scrambled cube (4.33·10^19 states), and G4 is a solved cube (1 state).
Instead of looking for a solution directly, the algorithm works by moving from one group to the other where each group
is treated as a "simpler" puzzle for the computer to solve.
By using a brute-force apporach (BFS) a computer can solve a cube using this algorithm in a relatively short amount of time,
but lookup tables can be used as heuristics in a search algorithm to speed solve times.

##### G0->G1:
- Positions: 4.33·10^19
- Unique states: 2^11 = 2048
- Legal moves: All moves
##### G1->G2:
- Positions: 2.11·10^16
- Unique states: 8C4 * 3^7 = 1082565
- Legal moves: 90-degre Up/Down turns are excluded
##### G2->G3:
- Positions: 1.95·10^10
- Unique states: 8C4 * (8C2 * 6C2 * 4C2 * 2C2) * 2 = 352800
- Legal moves: 90-degre Up/Down and Front/Back turns are excluded
##### G3->G4:
- Positions: 6.63·10^5
- Unique states: 96 * 4!^3 / 2 = 663552
- Legal moves: Only 180-degre moves are allowed (all 90-degre moves are excluded)


## Building
Set the working directory to the root project folder or run the executable from there

**Make sure that your compiler supports C++20**

##### Building on Linux
1. `sudo apt install cmake libsdl2-dev g++`

##### Building on Windows
1. Write the path to your SDL2 folder in CMakeLists.txt

To set the working directory to the root project folder in Visual Studio, change launch.vs.json accordingly:
```
"project": "CMakeLists.txt",
"projectTarget": "RubiksCubeSolver.exe",
"name": "RubiksCubeSolver.exe",
"currentDir": "path\\to\\root"
```


