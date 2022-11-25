#include "Level.h"

#include <utility>

Level::Level(std::string name, const Size &size, const Position &offset) : name(name), size(size), offset(offset) {}

const std::string &Level::getName() const {
    return name;
}

const Position &Level::getOffset() const {
    return offset;
}

const Size &Level::getSize() const {
    return size;
}

void Level::display(Terminal &terminal) const {
    displayBorderRow(-1, terminal);
    for (int i = 0; i < size.getRows(); i++) {
        displayInteriorRow(i, terminal);
    }
    displayBorderRow(size.getRows(), terminal);

//    displayPlayer();
}

void Level::displayBorderRow(int row, Terminal &terminal) const {
    terminal.display('+', {row, -1});

    for (int i = 0; i < size.getCols(); i++) {
        terminal.display('=', {row, i});
    }
    terminal.display('+', {row, size.getCols()});
}

void Level::displayInteriorRow(int row, Terminal &terminal) const {
    terminal.display('|', {row, -1});
    for (int i = 0; i < size.getCols(); i++) {
        terminal.display('.', {row, i});
    }
    terminal.display('|', {row, size.getCols()});
}
