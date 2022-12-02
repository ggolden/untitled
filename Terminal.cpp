#include <curses.h>
#include <iostream>
#include "Terminal.h"

Terminal::Terminal(bool debug) : debug(debug) {
    if (!debug) {
        initscr();
        curs_set(0);
        cbreak();

        // enable function key recognition, with a short delay after seeing the esc
        keypad(stdscr, true);
        set_escdelay(100);

//    timeout(0); // for non-blocking getch()
//        noecho();
//        clear(); // or erase()?
//        refresh();
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

void Terminal::display(int c, const Position &position) {
    Position offsetPosition = position + offset;

    if (!debug) {
        mvaddch(offsetPosition.getRow(), offsetPosition.getCol(), c);
    } else {
        std::cout << c << " @ " << offsetPosition.getRow() << "," << offsetPosition.getCol() << std::endl;
    }
}

int Terminal::read() {
    if (!debug) {
        return getch();
    } else {
        int c;
        std::cin >> c;
        return c;
    }
}
