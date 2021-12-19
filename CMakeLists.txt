cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project3)

## In most cases better set in the CMake cache
set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper main.cpp TextureManager.cpp TextureManager.h GameBoard.cpp GameBoard.h Tile.cpp Tile.h Random.cpp Random.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)