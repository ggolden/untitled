//
// Created by Glenn R. Golden on 11/21/22.
//
#include <iostream>
#include "Level.h"

Level::Level(const Size &size, const Position &offset, const Terminal &terminal) : size(size), offset(offset),
                                                                                   terminal(terminal) {}

const Size &Level::getSize() const {
    return size;
}

const Terminal &Level::getTerminal() const {
    return terminal;
}

void Level::display() {
//    std::cout << "Level size: " << size.getRows() << " x " << size.getCols() << std::endl;

    displayBorderRow(-1);
    for (int i = 0; i < size.getRows(); i++) {
        displayInteriorRow(i);
    }
    displayBorderRow(size.getRows());
}

void Level::displayBorderRow(int row) {
    terminal.display('+', Position(offset.getRow() + row, offset.getCol() + -1));

    for (int i = 0; i < size.getCols(); i++) {
        terminal.display('=', Position(offset.getRow() + row, offset.getCol() + i));
    }
    terminal.display('+', Position(offset.getRow() + row, offset.getCol() + size.getCols()));
}

void Level::displayInteriorRow(int row) {
    terminal.display('|', Position(offset.getRow() + row, offset.getCol() + -1));
    for (int i = 0; i < size.getCols(); i++) {
        terminal.display('.', Position(offset.getRow() + row, offset.getCol() + i));
    }
    terminal.display('|', Position(offset.getRow() + row, offset.getCol() + size.getCols()));
}
