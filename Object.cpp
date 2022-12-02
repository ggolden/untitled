#include "Object.h"

Object::Object(int displayChar, const Position &position, ObjectType type) : displayChar(displayChar),
                                                                             position(position), type(type) {}

int Object::getDisplayChar() const {
    return displayChar;
}

const Position &Object::getPosition() const {
    return position;
}

void Object::setPosition(const Position &newPosition) {
    position = newPosition;
}

ObjectType Object::getType() const {
    return type;
}

void Object::display(Terminal &terminal) {
    terminal.display(getDisplayChar(), getPosition());
}
