cmake_minimum_required(VERSION 3.5)

project(RubiksCubeSolver)

set(SRC "${CMAKE_SOURCE_DIR}/main.cpp"
        "${CMAKE_SOURCE_DIR}/Cube.cpp"
        "${CMAKE_SOURCE_DIR}/Engine/Engine.cpp"
        "${CMAKE_SOURCE_DIR}/Util/DatabaseGenerator.cpp"
        "${CMAKE_SOURCE_DIR}/Util/SearchUtil.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Database.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Searcher.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Thistlethwaite.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Databases/G0_G1_database.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Databases/G1_G2_database.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Databases/G2_G3_database.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Databases/G3_G4_database.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Goals/G0_G1_goal.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Goals/G1_G2_goal.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Goals/G2_G3_goal.cpp"
        "${CMAKE_SOURCE_DIR}/Solver/Thistlethwaite/Goals/G3_G4_goal.cpp")

add_executable(RubiksCubeSolver ${SRC})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -std=c++20")
set(CMAKE_BUILD_TYPE Release)

# SDL2
#    Linux
if(UNIX)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(RubiksCubeSolver PUBLIC SDL2::SDL2)
    # target_link_libraries(RubiksCubeSolver ${SDL2_LIBRARIES})
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
