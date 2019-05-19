cmake_minimum_required(VERSION 3.13)
project (chessBingen VERSION 1.1)
cmake_policy(SET CMP0076 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(gls ${CMAKE_SOURCE_DIR}/lib/)

add_executable(chessBingen)
target_sources(chessBingen PUBLIC src/main.cpp src/fenReader.cpp src/board.cpp src/pieces.cpp src/declarations.cpp src/search.cpp src/debug.cpp)
target_include_directories(chessBingen PUBLIC include lib )
target_link_directories(chessBingen PUBLIC lib)
