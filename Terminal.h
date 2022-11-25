#ifndef UNTITLED_TERMINAL_H
#define UNTITLED_TERMINAL_H

#include "Position.h"

class Terminal {
    bool debug;
    Position offset{0, 0}; // same as = Position(0,0);

public:
    explicit Terminal(bool debug = false);

    virtual ~Terminal();

    void setOffset(const Position &newOffset);

    void clearScreen();

    void refreshScreen();

    void display(char c, const Position &position);

    char read();
};

#endif //UNTITLED_TERMINAL_H
