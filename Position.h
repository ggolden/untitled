//
// Created by Glenn R. Golden on 11/21/22.
//

#ifndef UNTITLED_POSITION_H
#define UNTITLED_POSITION_H

class Position {

private:
public:
    Position(int row, int col);
    int getRow() const;
    int getCol() const;

private:
    int row;
    int col;
};

#endif //UNTITLED_POSITION_H
