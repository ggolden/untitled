#include "WinScreen.h"

void WinScreen::display(const Player &player, Terminal &terminal) {
    terminal.display("you win!", Position{10, 10});

    char buf[128];
    snprintf(buf, 128, "You had %d coins.", player.getCoins());
    terminal.display(buf, Position {12,10});
}