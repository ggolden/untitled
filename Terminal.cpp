#include <curses.h>
#include <iostream>
#include "Terminal.h"

Terminal::Terminal(bool debug) : debug(debug) {
    if (!debug) {
        initscr();
        curs_set(0);
//    timeout(0);
        noecho();
        erase(); // or clear() ?
        refresh();
    } else {
    }
}

Terminal::~Terminal() {
    if (!debug) {
        endwin();
    }
}

void Terminal::setOffset(const Position &newOffset) {
    Terminal::offset = newOffset;
}

void Terminal::clearScreen() {
    if (!debug) {
        erase(); // clear();
        refresh();
    } else {
        std::cout << "CLEAR" << std::endl << std::endl;
    }
}

void Terminal::display(char c, const Position &position) {
    Position offsetPosition = position + offset;

    if (!debug) {
        mvaddch(offsetPosition.getRow(), offsetPosition.getCol(), c);
        refresh();
    } else {
        std::cout << c << " @ " << offsetPosition.getRow() << "," << offsetPosition.getCol() << std::endl;
    }
}

char Terminal::read() {
    if (!debug) {
        return getch();
    } else {
        char c;
        std::cin >> c;
        return c;
    }
}
