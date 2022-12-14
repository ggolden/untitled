#ifndef UNTITLED_TERMINAL_H
#define UNTITLED_TERMINAL_H

#include "Position.h"

class Terminal {
    bool debug = false;
    Position offset{0, 0};

public:
    explicit Terminal(bool debug = false);

    virtual ~Terminal();

    void setOffset(const Position &newOffset);

    void clearScreen();

    void refreshScreen();

    void display(int c, const Position &position);

    void display(const char *str, const Position &position);

    int read();

    int rows();

    int cols();
};

#endif //UNTITLED_TERMINAL_H
