#ifndef UNTITLED_WINSCREEN_H
#define UNTITLED_WINSCREEN_H

#include "../Terminal.h"
#include "../objects/Player.h"

class WinScreen {
public:
    void display(const Player &player, Terminal &terminal);
};

#endif //UNTITLED_WINSCREEN_H
