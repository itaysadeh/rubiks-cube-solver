cmake_minimum_required(VERSION 3.5)

project(RubiksCubeSolver)

set(SRC "${CMAKE_SOURCE_DIR}/main.cpp"
         "${CMAKE_SOURCE_DIR}/Cube.cpp"
         "${CMAKE_SOURCE_DIR}/Util/DatabaseGenerator.cpp"
         "${CMAKE_SOURCE_DIR}/Util/MovesSimplifier.cpp"
         "${CMAKE_SOURCE_DIR}/Util/DatabaseGenerator.cpp"
         "${CMAKE_SOURCE_DIR}/Database/Database.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Solver.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Thistlethwaite.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Databases/G0_G1_database.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Databases/G1_G2_database.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Databases/G2_G3_database.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Databases/G3_G4_database.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Goals/G0_G1_goal.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Goals/G1_G2_goal.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Goals/G2_G3_goal.cpp"
         "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Groups/Goals/G3_G4_goal.cpp")

add_executable(RubiksCubeSolver ${SRC})

# C++20 required for rotl/rotr
set_property(TARGET RubiksCubeSolver PROPERTY CXX_STANDARD 20)
set_property(TARGET RubiksCubeSolver PROPERTY CXX_STANDARD_REQUIRED ON)

# SDL2
#    Linux
if(UNIX)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(RubiksCubeSolver ${SDL2_LIBRARIES})
endif()
#    Windows
if(WIN32)
# use this when SDL2 is installed somewhere else on your PC
    #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_PREFIX_PATH})
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(RubiksCubeSolver ${SDL2_LIBRARY})
endif()
