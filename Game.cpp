#include <iostream>
#include "Game.h"
#include "Level.h"
#include "Command.h"

Game::Game() {
    init();
}

void Game::init() {
    // construct levels
    levels.emplace_back("Singularity", Size(9, 14), Position(5, 5));
    levels.push_back(Level("DO NOT ENTER", Size(5, 5), Position(10, 10)));
}

Command Game::parse(char input) {
    switch (input) {
        case 'q':
            //case 27: // ESC
            return Command::QUIT;
        case 65: // arrow up
        case 'w':
            return Command::UP;
        case 67:
        case 'd':
            return Command::RIGHT;
        case 66:
        case 's':
            return Command::DOWN;
        case 68:
        case 'a':
            return Command::LEFT;
        default:
            return Command::OTHER;
    }
}

void Game::movePlayerIfPossible(const Position &delta) {
    Position newPosition = player.getPosition() + delta;
    Level &level = levels.at(player.getLevelIndex());
    Object objectAtPosition = level.getObjectAt(newPosition);
    if (objectAtPosition.getType() != ObjectType::WALL) {
        player.setPosition(newPosition);
    }
}

void Game::processPlayerMovement(Command command) {
    switch (command) {
        case Command::UP:
            movePlayerIfPossible(Position(-1, 0));
            break;
        case Command::RIGHT:
            movePlayerIfPossible(Position(0, 1));
            break;
        case Command::DOWN:
            movePlayerIfPossible(Position(1, 0));
            break;
        case Command::LEFT:
            movePlayerIfPossible(Position(0, -1));
            break;
        case Command::QUIT:
        case Command::OTHER:
            break;
    }
}

// return game running status
bool Game::processPlayerInteraction() {
    Level &level = levels.at(player.getLevelIndex());
    Object objectAtPosition = level.getObjectAt(player.getPosition());

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
        char input = terminal.read();
        Command command = parse(input);
        processPlayerMovement(command);
        bool gameRunning = processPlayerInteraction();

        if (command == Command::QUIT || !gameRunning) {
            break;
        }
    } while (true);
}
