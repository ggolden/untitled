#ifndef UNTITLED_OBJECT_H
#define UNTITLED_OBJECT_H

#include "../Position.h"
#include "ObjectType.h"
#include "../Terminal.h"

class Object {
    int displayChar;
    Position position;
    ObjectType type;

public:
    Object(int displayChar, const Position &position, ObjectType type);
    virtual ~Object() = default;

    int getDisplayChar() const;

    const Position &getPosition() const;

    void setPosition(const Position &newPosition);

    ObjectType getType() const;

    void display(Terminal &terminal) const;
};

#endif //UNTITLED_OBJECT_H
