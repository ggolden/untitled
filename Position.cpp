//
// Created by Glenn R. Golden on 11/21/22.
//

#include "Position.h"

Position::Position(int row, int col) : row(row), col(col) {}

int Position::getRow() const {
    return row;
}

int Position::getCol() const {
    return col;
}
