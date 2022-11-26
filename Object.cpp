//
// Created by Glenn R. Golden on 11/26/22.
//

#include "Object.h"

Object::Object(char displayChar, const Position &position, ObjectType type) : displayChar(displayChar),
                                                                              position(position), type(type) {}
char Object::getDisplayChar() const {
    return displayChar;
}

const Position &Object::getPosition() const {
    return position;
}

ObjectType Object::getType() const {
    return type;
}

void Object::display(Terminal &terminal) {
    terminal.display(getDisplayChar(), getPosition());
}
