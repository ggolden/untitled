cmake_minimum_required(VERSION 3.23)
project(untitled)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Game.cpp Game.h Level.cpp Level.h Size.cpp Size.h Terminal.cpp Terminal.h Position.cpp Position.h objects/Player.cpp objects/Player.h Command.h objects/Object.cpp objects/Object.h objects/ObjectType.h objects/Wall.cpp objects/Wall.h objects/Goal.cpp objects/Goal.h screens/Title.cpp screens/Title.h screens/WinScreen.cpp screens/WinScreen.h screens/LoseScreen.cpp screens/LoseScreen.h objects/Obstacle.cpp objects/Obstacle.h objects/Key.cpp objects/Key.h objects/Door.cpp objects/Door.h objects/Coin.cpp objects/Coin.h objects/StairsUp.cpp objects/StairsUp.h objects/StairsDown.cpp objects/StairsDown.h objects/Bouncer.cpp objects/Bouncer.h objects/Rando.cpp objects/Rando.h objects/ActiveObject.cpp objects/ActiveObject.h)

target_link_libraries(untitled ${CURSES_LIBRARIES})