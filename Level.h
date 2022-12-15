#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <memory>
#include <string>
#include <vector>
#include "Position.h"
#include "Terminal.h"
#include "objects/Object.h"
#include "Size.h"

class Level {
    std::string name;
    std::vector<std::unique_ptr<Object>> objects;

    void putObject(Object * object);

public:
    explicit Level(std::string name);

    const std::string &getName() const;

    void display(Terminal &terminal) const;

    const Object * getObjectAt(const Position &position) const;

    std::unique_ptr<Object> deleteObjectAt(const Position &position);

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
