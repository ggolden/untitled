#include <utility>

#include "Level.h"
#include "objects/Goal.h"
#include "objects/Obstacle.h"
#include "objects/Wall.h"
#include "objects/Key.h"
#include "objects/Door.h"
#include "objects/Coin.h"
#include "objects/StairsUp.h"
#include "objects/StairsDown.h"
#include "objects/Player.h"
#include "objects/Bouncer.h"
#include "objects/Rando.h"

Level::Level(std::string name, int visibilityDistance) : name(std::move(name)),
                                                         visibilityDistance(visibilityDistance) {}

void Level::putObject(Object *object) {
    objects.push_back(std::unique_ptr<Object>(object));
}

void Level::putActiveObject(ActiveObject *object) {
    objects.push_back(std::unique_ptr<ActiveObject>(object));
}

bool Level::shouldObjectDisplay(const Position &playerPosition, const Position &objectPosition) const {
    return (objectPosition.distance(playerPosition) <= visibilityDistance);
}

const std::string &Level::getName() const {
    return name;
}

void Level::display(const Player &player, Terminal &terminal) const {
    for (auto &object: objects) {
        if (shouldObjectDisplay(player.getPosition(), object->getPosition())) {
            object->display(terminal);
        }
    }
    for (auto &object: activeObjects) {
        if (shouldObjectDisplay(player.getPosition(), object->getPosition())) {
            object->display(terminal);
        }
    }
}

void Level::tick(Player &player) {
    for (auto &object: activeObjects) {
        object->act(player);
    }
}

const Object *Level::getObjectAt(const Position &position) const {
    for (auto &object: objects) {
        if (object->getPosition() == position) {
            return object.get();
        }
    }

    return nullptr;
}

std::unique_ptr<Object> Level::deleteObjectAt(const Position &position) {
    for (auto i = 0; i < objects.size(); i++) {
        if (objects[i]->getPosition() == position) {
            std::unique_ptr<Object> rv = std::move(objects[i]);
            objects.erase(objects.begin() + i);
            return rv;
        }
    }
    return {nullptr};
}

void Level::addRoom(const Size &size, const Position &position) {
    putObject(new Wall(Wall::CORNER, Position(0, 0) + position));
    for (auto col = 1; col < size.getCols() - 1; col++) {
        putObject(new Wall(Wall::HORIZONTAL, Position(0, col) + position));
    }
    putObject(new Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));

    for (auto row = 1; row < size.getRows() - 1; row++) {
        putObject(new Wall(Wall::VERTICAL, Position(row, 0) + position));
        putObject(new Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + position));
    }

    putObject(new Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    for (auto col = 1; col < size.getCols() - 1; col++) {
        putObject(new Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + position));
    }
    putObject(new Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + position));
}

void Level::addHorizontalHall(int length, const Position &position) {
    Size size{3, length};

    for (auto row = 0; row < size.getRows(); row++) {
        deleteObjectAt(position + Position(row, 0));
        deleteObjectAt(position + Position(row, size.getCols() - 1));
    }

    putObject(new Wall(Wall::CORNER, Position(0, 0) + position));
    putObject(new Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    for (auto col = 1; col < size.getCols() - 1; col++) {
        putObject(new Wall(Wall::HORIZONTAL, Position(0, col) + position));
        putObject(new Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + position));
    }
    putObject(new Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));
    putObject(new Wall(Wall::CORNER, Position(size.getRows() - 1, length - 1) + position));
}

void Level::addVerticalHall(int length, const Position &position) {
    Size size{length, 3};

    for (auto col = 0; col < size.getCols(); col++) {
        deleteObjectAt(position + Position(0, col));
        deleteObjectAt(position + Position(size.getRows() - 1, col));
    }

    putObject(new Wall(Wall::CORNER, Position(0, 0) + position));
    putObject(new Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));
    for (auto row = 1; row < size.getRows() - 1; row++) {
        putObject(new Wall(Wall::VERTICAL, Position(row, 0) + position));
        putObject(new Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + position));
    }
    putObject(new Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    putObject(new Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + position));
}

void Level::addGoal(const Position &position) {
    putObject(new Goal(position));
}

void Level::addObstacle(const Position &position) {
    putObject(new Obstacle(position));
}

void Level::addKey(const Position &position) {
    putObject(new Key(position));
}

void Level::addDoor(const Position &position) {
    putObject(new Door(position));
}

void Level::addCoin(const Position &position, int value) {
    putObject(new Coin(position, value));
}

void Level::addStairsUp(const Position &position) {
    putObject(new StairsUp(position));
}

void Level::addStairsDown(const Position &position) {
    putObject(new StairsDown(position));
}

void Level::addBouncer(const Position &position) {
    putActiveObject(new Bouncer(position));
}

void Level::addRando(const Position &position) {
    putActiveObject(new Rando(position));
}

Position Level::addBlueprint(const std::string &level, int width = 80) {
    int row = 0;
    int col = 0;
    Position playerPosition{1, 1};
    for (char c: level) {
        switch (c) {
            case '+':
                putObject(new Wall(Wall::CORNER, Position(row, col)));
                break;
            case '=':
                putObject(new Wall(Wall::HORIZONTAL, Position(row, col)));
                break;
            case '|':
                putObject(new Wall(Wall::VERTICAL, Position(row, col)));
                break;
            case '@':
                playerPosition = {row, col};
                break;
            case '#':
                addObstacle(Position{row, col});
                break;
            case 'P':
                addGoal(Position{row, col});
                break;
            case 'K':
                addKey(Position{row, col});
                break;
            case 'D':
                addDoor(Position{row, col});
                break;
            case 'c':
                addCoin(Position{row, col}, 1);
                break;
            case 'C':
                addCoin(Position{row, col}, 10);
                break;
            case '^':
                addStairsUp(Position{row, col});
                break;
            case 'v':
                addStairsDown(Position{row, col});
                break;
            case 'R':
                addRando(Position{row, col});
                break;
            case 'B':
                addBouncer(Position{row, col});
                break;
            default:
                break;
        }
        col++;
        if (col >= width) {
            col = 0;
            row++;
        }
    }
    return playerPosition;
}
