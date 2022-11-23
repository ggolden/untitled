//
// Created by Glenn R. Golden on 11/21/22.
//

#include <curses.h>
#include "Terminal.h"

Terminal::Terminal() {
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    clear();
    refresh();
}

Terminal::~Terminal() {
    endwin();
}

void Terminal::clearScreen() {
    clear();
    refresh();
}

void Terminal::display(char c, Position position) {
    mvaddch(position.getRow(), position.getCol(), c);
    refresh();
}
