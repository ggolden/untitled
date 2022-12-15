#include <utility>

#include "Level.h"
#include "objects/Goal.h"
#include "objects/Obstacle.h"
#include "objects/Wall.h"
#include "objects/Key.h"
#include "objects/Door.h"
#include "objects/Coin.h"

Level::Level(std::string name) : name(std::move(name)) {}

void Level::putObject(Object *object) {
    objects.push_back(std::unique_ptr<Object>(object));
}

const std::string &Level::getName() const {
    return name;
}

void Level::display(Terminal &terminal) const {
    for (auto &object: objects) {
        object->display(terminal);
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
