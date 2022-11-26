//
// Created by Glenn R. Golden on 11/21/22.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include <vector>
#include "Level.h"
#include "Terminal.h"
#include "Player.h"
#include "Command.h"

class Game {
    std::vector<Level> levels;
    Player player;

    void init();
    static Command parse(char input);
    void processPlayerMovement(Command command);
    void movePlayerIfPossible(const Position & delta);
    bool processPlayerInteraction();

public:
    Game();

    void play(Terminal &terminal);
};

#endif //UNTITLED_GAME_H
