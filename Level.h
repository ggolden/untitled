//
// Created by Glenn R. Golden on 11/21/22.
//

#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include "Size.h"
#include "Terminal.h"

class Level {
public:
    Level(const Size &size, const Position &offset, const Terminal &terminal);

    void display();

    const Size &getSize() const;
    const Terminal &getTerminal() const;

private:
    void displayBorderRow(int row);
    void displayInteriorRow(int row);

    Size size;
    Position offset;
    Terminal terminal;
};

#endif //UNTITLED_LEVEL_H
