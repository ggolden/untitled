#include "LoseScreen.h"

void LoseScreen::display(const Player & player, Terminal &terminal) {
    terminal.display("you lose!", Position {10,10});

    terminal.display(player.getMessage().c_str(), Position {11,10});

    char buf[128];
    snprintf(buf, 128, "You had %d coins.", player.getCoins());
    terminal.display(buf, Position {13,10});
}