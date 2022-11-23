//
// Created by Glenn R. Golden on 11/21/22.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include "Level.h"
#include "Terminal.h"

class Game {
public:
    Game(const Terminal &termainal, const Level &level);

    const Level& getLevel() const;

    void start();

private:
    Level level;
    Terminal terminal;
};


#endif //UNTITLED_GAME_H
