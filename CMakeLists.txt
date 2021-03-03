cmake_minimum_required(VERSION 3.5)

project(RubiksCubeSolver)

set(SRC "${CMAKE_SOURCE_DIR}/main.cpp"
         "${CMAKE_SOURCE_DIR}/Cube.cpp"
         "${CMAKE_SOURCE_DIR}/Engine/Engine.cpp"
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

# The relative path of the output will be /root (working directory)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

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
    # Change to your local SDL2 folder path
    set(SDL2_DIR "D:/dev/sdks/SDL2")

    # Sets working directory to root if the Visual Studio generator is used
    set_target_properties(RubiksCubeSolver PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    find_package(SDL2 REQUIRED)

    # Copy SDL2.dll to the .exe file
    add_custom_command(TARGET RubiksCubeSolver POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${SDL2_DIR}/lib/x64/SDL2.dll"              
                $<TARGET_FILE_DIR:RubiksCubeSolver>)

    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(RubiksCubeSolver ${SDL2_LIBRARIES})
endif()
