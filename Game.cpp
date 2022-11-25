#include "Game.h"
#include "Level.h"

Game::Game() {
    init();
}

void Game::init() {
    // construct levels
    // could be push_back()
    levels.push_back(Level("Singularity", Size(20, 20), Position(5, 5)));
    levels.push_back(Level("DO NOT ENTER", Size(5, 5), Position(10, 10)));
}

void Game::play(Terminal &terminal) {
    // display all things in the current level

    // setup for displaying the current level
    Level &level = levels.at(player.getLevelIndex());
    terminal.setOffset(level.getOffset());

    level.display(terminal);
    player.display(terminal);

    // get and act on input
    terminal.read();
}
