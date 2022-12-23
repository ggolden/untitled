#include "Game.h"
#include "Terminal.h"

int main() {
    srand(time(nullptr));

    Terminal terminal;
    Game game;

    game.play(terminal);

    return 0;
}
