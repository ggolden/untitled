#ifndef UNTITLED_ROOM_H
#define UNTITLED_ROOM_H

#include <vector>
#include "Size.h"
#include "Position.h"
#include "objects/Object.h"

class Room {
    Size size;
    Position offset;

    void addWalls(std::vector<Object> &objects);

public:
    Room(const Size &size, const Position &offset);
    void init(std::vector<Object> &objects);
};

#endif //UNTITLED_ROOM_H
