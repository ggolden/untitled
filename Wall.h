#ifndef UNTITLED_WALL_H
#define UNTITLED_WALL_H

#include "Object.h"

class Wall : public Object {
public:
    enum WallType {
        HORIZONTAL = '=', VERTICAL = '|', CORNER = '+'
    };

    Wall(WallType type, const Position &position);
};

#endif //UNTITLED_WALL_H
