//
// Created by Glenn R. Golden on 11/21/22.
//

#include <curses.h>
#include "Game.h"

Game::Game(const Terminal &terminal, const Level &level) : terminal(terminal), level(level) {}

const Level &Game::getLevel() const {
    return level;
}

void Game::start() {
    level.display();

    getch();
}
