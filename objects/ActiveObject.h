#ifndef UNTITLED_ACTIVEOBJECT_H
#define UNTITLED_ACTIVEOBJECT_H

#include "Object.h"
#include "Player.h"

class Level;

class ActiveObject : public Object {
public:
    ActiveObject(int displayChar, const Position &position, ObjectType type);

    virtual void act(Player &player, const Level &level) = 0;
};

#endif //UNTITLED_ACTIVEOBJECT_H
