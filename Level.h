#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <memory>
#include <string>
#include <vector>
#include "Position.h"
#include "Terminal.h"
#include "objects/Object.h"
#include "Size.h"
#include "objects/Player.h"
#include "objects/ActiveObject.h"

class Level {
    std::string name;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<ActiveObject>> activeObjects;
    int visibilityDistance;

    void putObject(Object *object);

    void putActiveObject(ActiveObject *object);

    bool shouldObjectDisplay(const Position &playerPosition, const Position &objectPosition) const;

public:
    explicit Level(std::string name, int visibilityDistance);

    const std::string &getName() const;

    void display(const Player &player, Terminal &terminal) const;

    void tick(Player &player);

    const Object *getObjectAt(const Position &position) const;

    std::unique_ptr<Object> deleteObjectAt(const Position &position);

    void addRoom(const Size &size, const Position &position);

    void addHorizontalHall(int length, const Position &position);

    void addVerticalHall(int length, const Position &position);

    void addGoal(const Position &position);

    void addObstacle(const Position &position);

    void addKey(const Position &position);

    void addDoor(const Position &position);

    void addCoin(const Position &position, int value);

    void addStairsUp(const Position &position);

    void addStairsDown(const Position &position);

    void addBouncer(const Position &position);

    void addRando(const Position &position);

    Position addBlueprint(const std::string &level, int width);
};

#endif //UNTITLED_LEVEL_H
