//
// Created by Glenn R. Golden on 11/21/22.
//

#ifndef UNTITLED_SIZE_H
#define UNTITLED_SIZE_H


class Size {
public:
    Size(int rows, int cols);
    int getRows() const;
    int getCols() const;

private:
    int rows;
    int cols;
};


#endif //UNTITLED_SIZE_H
