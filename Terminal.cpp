#include <curses.h>
#include <iostream>
#include "Terminal.h"

Terminal::Terminal(bool debug) : debug(debug) {
    if (!debug) {
        initscr();
        curs_set(0);
//    timeout(0); // for non-blocking getch()
        noecho();
        clear(); // or erase()?
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
    } else {
        std::cout << "CLEAR" << std::endl << std::endl;
    }
}

void Terminal::refreshScreen() {
    if (!debug) {
        refresh();
    } else {
        std::cout << "REFRESH" << std::endl << std::endl;
    }
}

void Terminal::display(char c, const Position &position) {
    Position offsetPosition = position + offset;

    if (!debug) {
        mvaddch(offsetPosition.getRow(), offsetPosition.getCol(), c);
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
