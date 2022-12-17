#ifndef UNTITLED_LOSESCREEN_H
#define UNTITLED_LOSESCREEN_H

#include "../Terminal.h"
#include "../objects/Player.h"

class LoseScreen {
public:
    void display(const Player &player, Terminal &terminal);
};

#endif //UNTITLED_LOSESCREEN_H
