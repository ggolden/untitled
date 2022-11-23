//
// Created by Glenn R. Golden on 11/21/22.
//

#ifndef UNTITLED_TERMINAL_H
#define UNTITLED_TERMINAL_H

#include "Position.h"

class Terminal {
public:
    virtual ~Terminal();

    Terminal();
    void clearScreen();
    void display(char c, Position position);

private:
};


#endif //UNTITLED_TERMINAL_H
