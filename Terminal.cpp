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

        // timeout(0); // TODO: for non-blocking getch()

    } else {
        std::cout << "Terminal()" << std::endl;
    }
}

Terminal::~Terminal() {
    if (!debug) {
        endwin();
    } else {
        std::cout << "~Terminal init" << std::endl;
    }
}

void Terminal::setOffset(const Position &newOffset) {
    Terminal::offset = newOffset;
}

void Terminal::clearScreen() {
    if (!debug) {
        erase(); // clear();
    } else {
        std::cout << "CLEAR" << std::endl;
    }
}

void Terminal::refreshScreen() {
    if (!debug) {
        refresh();
    } else {
        std::cout << "REFRESH" << std::endl;
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

void Terminal::display(const char *str, const Position &position) {
    Position offsetPosition = position + offset;
    if (!debug) {
        mvaddstr(offsetPosition.getRow(), offsetPosition.getCol(), str);
    } else {
        std::cout << str << " @ " << offsetPosition.getRow() << "," << offsetPosition.getCol() << std::endl;
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

int Terminal::rows() {
    if (!debug) {
        return LINES;
    } else {
        return 24;
    }
}

int Terminal::cols() {
    if (!debug) {
        return COLS;
    } else {
        return 80;
    }
}
