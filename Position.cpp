#include "Position.h"

Position::Position(int row, int col) : row(row), col(col) {}

int Position::getRow() const {
    return row;
}

int Position::getCol() const {
    return col;
}

Position Position::operator+(const Position &positionToAdd) const {
    // return Position(row + positionToAdd.getRow(), col + positionToAdd.getCol());
    return {row + positionToAdd.getRow(), col + positionToAdd.getCol()};
}
