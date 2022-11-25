#include <curses.h>
#include <iostream>
#include "Game.h"
#include "Level.h"
#include "Command.h"

Game::Game() {
    init();
}

void Game::init() {
    // construct levels
    // could be push_back()
    levels.push_back(Level("Singularity", Size(20, 20), Position(5, 5)));
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

void Game::process(Command command) {
    switch (command) {
        case Command::UP:
            movePlayer(Position(-1, 0));
            break;
        case Command::RIGHT:
            movePlayer(Position(0, 1));
            break;
        case Command::DOWN:
            movePlayer(Position(1, 0));
            break;
        case Command::LEFT:
            movePlayer(Position(0, -1));
            break;
        case Command::QUIT:
        case Command::OTHER:
            break;
    }
}

void Game::movePlayer(const Position &delta) {
    Position newPosition = player.getPosition() + delta;
    Level &level = levels.at(player.getLevelIndex());

    if (newPosition.getRow() >= 0 && //
        newPosition.getRow() < level.getSize().getRows() && //
        newPosition.getCol() >= 0 && //
        newPosition.getCol() < level.getSize().getCols()) {
        player.setPosition(newPosition);
    }
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

        // get and act on input
        char input = terminal.read();
        Command command = parse(input);
        process(command);

        if (command == Command::QUIT) {
            break;
        }
    } while (true);
}
