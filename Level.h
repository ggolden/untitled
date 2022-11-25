#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <string>
#include "Size.h"
#include "Terminal.h"
#include "Player.h"

class Level {
    std::string name;
    Size size;
    Position offset;

    void displayBorderRow(int row, Terminal &terminal) const;

    void displayInteriorRow(int row, Terminal &terminal) const;

public:
    Level(std::string name, const Size &size, const Position &offset);

    const std::string &getName() const;

    const Position &getOffset() const;

    void display(Terminal &terminal) const;
};

#endif //UNTITLED_LEVEL_H
