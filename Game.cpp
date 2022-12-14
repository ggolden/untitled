#include <iostream>
#include <curses.h>

#include "Game.h"
#include "Level.h"
#include "Command.h"
#include "screens/Title.h"
#include "screens/WinScreen.h"
#include "screens/LoseScreen.h"
#include "objects/Key.h"
#include "objects/Door.h"
#include "objects/Obstacle.h"
#include "objects/Goal.h"
#include "objects/Coin.h"

#define ESC 0x1b

Game::Game() {
    init();
}

// @formatter:off
std::string Game::level0{""
"+=====================================+........................................."
"|@..VR................................|......+================+................."
"|.....v..........#......c.............|......|................|................."
"|............#...................#....+======+................|................."
"|.....#...............................D....................#..|................."
"|..........C........#............#....+======+........#.......|................."
"|..B..................................|......|..........B.....|................."
"+===========+...+=====================+......|.......#..VP....|................."
"............|...|............................|................|................."
"............|...|............................+================+................."
"............|...|..............................................................."
"............|...|..............................................................."
"....+=======+...+========+....................+===============+................."
"....|....................|....................|...............|................."
"....|....#...............|....................|....C..........|................."
"....|....................|....................|...............|................."
"....+====================+....................+===============+................."
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
};

std::string Game::level1{""
"+=====================================+........................................."
"|.....................................|........................................."
"|.....^...............................|........................................."
"|...K.................................|........................................."
"|.....................................|........................................."
"|.....................................|........................................."
"|.....................................|........................................."
"+===============+=====================+........................................."
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
"................................................................................"
};
// @formatter:on

void Game::init() {
    Level level0("Level0", 9);
    Position playerPosition = level0.addBlueprint(Game::level0, 80);
//    level.addRoom(Size(19, 14), Position(0, 0));
//    level.addRoom(Size(19, 14), Position(3, 25));
//    level.addRoom(Size(5, 5), Position(28, 4));
//
//    level.addHorizontalHall(13, Position(8, 13));
//    level.addVerticalHall(11, Position(18, 5));
//
//    level.addObstacle(Position(7, 3));
//    level.addGoal(Position(5, 29));

    levels.push_back(std::move(level0));

    Level level1("Level1", 5);
    level1.addBlueprint(Game::level1, 80);
    levels.push_back(std::move(level1));

    player.setPosition(playerPosition);
}

Command Game::parse(int input) {
    switch (input) {
        case 'q':
        case ESC:
            return Command::QUIT;

        case KEY_UP:
        case 'w':
            return Command::UP;

        case KEY_RIGHT:
        case 'd':
            return Command::RIGHT;

        case KEY_DOWN:
        case 's':
            return Command::DOWN;

        case KEY_LEFT:
        case 'a':
            return Command::LEFT;

        default:
            return Command::OTHER;
    }
}

void Game::movePlayerIfPossible(const Position &newPosition, const Object *objectAtPosition, Level &level) {
    if (!objectAtPosition) {
        player.setPosition(newPosition);
        return;
    }

    if (objectAtPosition->getType() == ObjectType::DOOR) {
        if (player.hasInInventory(ObjectType::KEY)) {
            level.deleteObjectAt(objectAtPosition->getPosition());
        }
    } else if (objectAtPosition->getType() == ObjectType::STAIRS_DOWN) {
        player.setLevelIndex(player.getLevelIndex() + 1);
    } else if (objectAtPosition->getType() == ObjectType::STAIRS_UP) {
        player.setLevelIndex(player.getLevelIndex() - 1);
    } else if (objectAtPosition->getType() != ObjectType::WALL) {
        player.setPosition(newPosition);
    }
}

Position Game::computeNewPlayerPosition(Command command) {
    switch (command) {
        case Command::UP:
            return player.getPosition() + Position{-1, 0};
        case Command::RIGHT:
            return player.getPosition() + Position{0, 1};
        case Command::DOWN:
            return player.getPosition() + Position(1, 0);
        case Command::LEFT:
            return player.getPosition() + Position(0, -1);
        default:
            return player.getPosition();
    }
}

void Game::processPlayerInteraction(const Object *objectAtPosition, Level &level) {
    if (!objectAtPosition) {
        return;
    }

    switch (objectAtPosition->getType()) {
        case ObjectType::GOAL: {
            player.setWon(true);
            break;
        }
        case ObjectType::OBSTACLE: {
            player.kill("You ran into an obstacle!");
            break;
        }
        case ObjectType::KEY: {
            auto key = level.deleteObjectAt(objectAtPosition->getPosition());
            if (key) {
                player.addToInventory(key);
            }
            break;
        }
        case ObjectType::COIN: {
            auto coinObj = level.deleteObjectAt(objectAtPosition->getPosition());
            if (coinObj) {
                const Coin *coin = dynamic_cast<const Coin *>(coinObj.get());
                if (coin) {
                    player.addToCoins(coin->getAmount());
                }
            }
            break;
        }
        case ObjectType::BOUNCER:
        case ObjectType::RANDO: {
            player.kill("You ran into a bouncer/rando!");
            break;
        }
        default:
            break;
    }
}

void Game::showTitle(Terminal &terminal) {
    Title title;

    terminal.clearScreen();
    title.display(terminal);
    terminal.read();
}

void Game::showEndScreen(Terminal &terminal) {
    terminal.clearScreen();
    if (player.didWin()) {
        WinScreen winScreen;
        winScreen.display(player, terminal);
    } else {
        LoseScreen loseScreen;
        loseScreen.display(player, terminal);
    }
    terminal.read();
}

void Game::gameLoop(Terminal &terminal) {
    do {
        terminal.clearScreen();

        // display the UI
        terminal.setOffset({0, 0});
        char buf[128];
        snprintf(buf, 128, "Coins: %d", player.getCoins());
        terminal.display(buf, Position{1, 0});

        if (player.hasInInventory(ObjectType::KEY)) {
            terminal.display("Key!", Position{1, 15});
        }

        // display all things in the current level

        // setup for displaying the current level
        terminal.setOffset({3, 0});
        Level &level = levels.at(player.getLevelIndex());

        level.display(player, terminal);
        player.display(terminal);

        terminal.refreshScreen();

        // get and act on input
        int input = terminal.read();
        Command command = parse(input);
        Position newPlayerPosition = computeNewPlayerPosition(command);
        auto objectAtPosition = level.getObjectAt(newPlayerPosition);
        movePlayerIfPossible(newPlayerPosition, objectAtPosition, level);
        processPlayerInteraction(objectAtPosition, level);

        if (command == Command::QUIT) {
            break;
        }

        Level &newLevel = levels.at(player.getLevelIndex());
        newLevel.tick(player);

    } while (!player.didWin() && player.isAlive());
}

void Game::play(Terminal &terminal) {
    showTitle(terminal);
    gameLoop(terminal);
    showEndScreen(terminal);
}
