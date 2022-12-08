#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <string>
#include <vector>
#include "Position.h"
#include "Terminal.h"
#include "objects/Object.h"
#include "Room.h"

class Level {
    std::string name;
    std::vector<Object> objects;
    std::vector<Room> rooms;

    void init();
    void createRooms();
    void createGoal();
    void createObstacles();

public:
    Level(std::string name);

    const std::string &getName() const;

    void display(Terminal &terminal) const;

    Object getObjectAt(const Position &position) const;

    void deleteObjectAt(const Position &position);
};

#endif //UNTITLED_LEVEL_H
