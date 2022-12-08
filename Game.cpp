#include <iostream>
#include <curses.h>
#include "Game.h"
#include "Level.h"
#include "Command.h"
#include "screens/Title.h"
#include "screens/WinScreen.h"
#include "screens/LoseScreen.h"

#define ESC 0x1b

Game::Game() {
    init();
}

void Game::init() {
    levels.emplace_back("Singularity");
    levels.emplace_back("DO NOT ENTER");
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

void Game::movePlayerIfPossible(const Position &newPosition, const Object &objectAtPosition) {
    if (objectAtPosition.getType() != ObjectType::WALL) {
        player.setPosition(newPosition);
    }
}

Position Game::computeNewPlayerPosition(Command command) {
    switch (command) {
        case Command::UP:
            return player.getPosition() + Position {-1, 0};
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

bool Game::processPlayerInteraction(const Object &objectAtPosition) {
    bool goalAchieved = objectAtPosition.getType() == ObjectType::GOAL;
    if (goalAchieved) {
        player.setWon(true);
        return false;
    }

    bool obstacle = objectAtPosition.getType() == ObjectType::OBSTACLE;
    if (obstacle) {
        player.setWon(false);
        return false;
    }

    return true;
}

void Game::showTitle(Terminal &terminal) {
    Title title;

    terminal.clearScreen();
    title.display(terminal);
    terminal.read();
}

void Game::showEndScreen(Terminal &terminal) {
    terminal.clearScreen();;
    if (player.didWin()) {
         WinScreen winScreen;
         winScreen.display(terminal);
    } else {
        LoseScreen loseScreen;
        loseScreen.display(terminal);
    }
    terminal.read();
}

void Game::gameLoop(Terminal &terminal) {
    do {
        terminal.clearScreen();

        // display all things in the current level

        // setup for displaying the current level
        Level &level = levels.at(player.getLevelIndex());
//        terminal.setOffset(level.getOffset());

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

void Game::play(Terminal &terminal) {
    showTitle(terminal);
    gameLoop(terminal);
    showEndScreen(terminal);
}
