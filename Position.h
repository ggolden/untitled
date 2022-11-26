#ifndef UNTITLED_POSITION_H
#define UNTITLED_POSITION_H

class Position {
    int row = 0;
    int col = 0;

public:
    Position(int row, int col);

    int getRow() const;

    int getCol() const;

    Position operator+(const Position &positionToAdd) const;

    bool operator==(const Position &otherPosition) const;
};

#endif //UNTITLED_POSITION_H
