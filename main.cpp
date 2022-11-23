#include <iostream>
#include "Game.h"
#include "Terminal.h"

int main() {
    Terminal terminal;

    // std::cout << "untitled dungeon game" << std::endl;

    Size levelSize = Size(20, 20);
    Position levelPosition = Position (5, 5);
    Level gameLevel = Level(levelSize, levelPosition, terminal);
    Game game(terminal, gameLevel);

    game.start();

    return 0;
}
