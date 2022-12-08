//
// Created by Glenn R. Golden on 12/8/22.
//

#include "LoseScreen.h"

void LoseScreen::display(Terminal &terminal) {
    terminal.display("you lose!", Position {10,10});
}