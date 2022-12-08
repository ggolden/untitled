//
// Created by Glenn R. Golden on 12/8/22.
//

#include "WinScreen.h"

void WinScreen::display(Terminal &terminal) {
    terminal.display("you win!", Position {10,10});
}