//
// Created by Glenn R. Golden on 11/26/22.
//

#ifndef UNTITLED_OBJECT_H
#define UNTITLED_OBJECT_H


#include "Position.h"
#include "ObjectType.h"
#include "Terminal.h"

class Object {
    char displayChar;
    Position position;
    ObjectType type;

public:
    Object(char displayChar, const Position &position, ObjectType type);

    void display(Terminal &terminal);

    char getDisplayChar() const;

    const Position &getPosition() const;

    ObjectType getType() const;
};


#endif //UNTITLED_OBJECT_H
