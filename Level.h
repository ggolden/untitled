#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <string>
#include <vector>
#include "Position.h"
#include "Terminal.h"
#include "objects/Object.h"
#include "Size.h"

class Level {
    std::string name;
    std::vector<Object> objects;

    void putObject(const Object &object);

public:
    explicit Level(std::string name);

    const std::string &getName() const;

    void display(Terminal &terminal) const;

    Object getObjectAt(const Position &position) const;

    void deleteObjectAt(const Position &position);

    void addRoom(const Size &size, const Position &position);

    void addHorizontalHall(int length, const Position &position);

    void addVerticalHall(int length, const Position &position);

    void addGoal(const Position &position);

    void addObstacle(const Position &position);

    void addKey(const Position &position);

    void addDoor(const Position &position);

    void addCoin(const Position &position, int value);

    Position addBlueprint(const std::string &level, int width);
};

#endif //UNTITLED_LEVEL_H
