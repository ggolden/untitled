#include <iostream>
#include <curses.h>
#include "Game.h"
#include "Level.h"
#include "Command.h"

Game::Game() {
    init();
}

void Game::init() {
    // construct levels
    levels.emplace_back("Singularity", Size(9, 14), Position(5, 5));
    levels.emplace_back("DO NOT ENTER", Size(5, 5), Position(10, 10));
}

Command Game::parse(int input) {
    switch (input) {
        case 'q':
        case 0x1b: // ESC
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

void Game::movePlayerIfPossible(const Position &newPosition, const Object &objectAtPosition) {
    if (objectAtPosition.getType() != ObjectType::WALL) {
        player.setPosition(newPosition);
    }
}

Position Game::computeNewPlayerPosition(Command command) {
    switch (command) {
        case Command::UP:
            return player.getPosition() + Position(-1, 0);
        case Command::RIGHT:
            return player.getPosition() + Position(0, 1);
        case Command::DOWN:
            return player.getPosition() + Position(1, 0);
        case Command::LEFT:
            return player.getPosition() + Position(0, -1);
        default:
            return player.getPosition();
    }
}

bool Game::processPlayerInteraction(const Object &objectAtPosition) {
    bool goalAchieved = objectAtPosition.getType() == ObjectType::GOAL;
    return !goalAchieved;
}

void Game::play(Terminal &terminal) {
    do {
        terminal.clearScreen();

        // display all things in the current level

        // setup for displaying the current level
        Level &level = levels.at(player.getLevelIndex());
        terminal.setOffset(level.getOffset());

        level.display(terminal);
        player.display(terminal);

        terminal.refreshScreen();

        // get and act on input
        int input = terminal.read();
        Command command = parse(input);
        Position newPlayerPosition = computeNewPlayerPosition(command);
        Object objectAtPosition = level.getObjectAt(newPlayerPosition);
        movePlayerIfPossible(newPlayerPosition, objectAtPosition);
        bool gameRunning = processPlayerInteraction(objectAtPosition);

        if (command == Command::QUIT || !gameRunning) {
            break;
        }
    } while (true);
}
