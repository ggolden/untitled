cmake_minimum_required(VERSION 3.23)
project(untitled)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Game.cpp Game.h Level.cpp Level.h Size.cpp Size.h Terminal.cpp Terminal.h Position.cpp Position.h Player.cpp Player.h)

target_link_libraries(untitled ${CURSES_LIBRARIES})