#include <utility>

#include "Level.h"
#include "objects/Goal.h"
#include "objects/Obstacle.h"
#include "objects/Wall.h"
#include "objects/Key.h"
#include "objects/Door.h"
#include "objects/Coin.h"

Level::Level(std::string name) : name(std::move(name)) {}

void Level::putObject(const Object &object) {
    objects.push_back(object);
}

const std::string &Level::getName() const {
    return name;
}

void Level::display(Terminal &terminal) const {
    for (auto &object: objects) {
        object.display(terminal);
    }
}

Object Level::getObjectAt(const Position &position) const {
    for (auto &object: objects) {
        if (object.getPosition() == position) {
            return object;
        }
    }

    return {' ', position, ObjectType::SPACE};
}

void Level::deleteObjectAt(const Position &position) {
    for (auto i = 0; i < objects.size(); i++) {
        if (objects.at(i).getPosition() == position) {
            objects.erase(objects.begin() + i);
            break;
        }
    }
}

void Level::addRoom(const Size &size, const Position &position) {
    putObject(Wall(Wall::CORNER, Position(0, 0) + position));
    for (auto col = 1; col < size.getCols() - 1; col++) {
        putObject(Wall(Wall::HORIZONTAL, Position(0, col) + position));
    }
    putObject(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));

    for (auto row = 1; row < size.getRows() - 1; row++) {
        putObject(Wall(Wall::VERTICAL, Position(row, 0) + position));
        putObject(Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + position));
    }

    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    for (auto col = 1; col < size.getCols() - 1; col++) {
        putObject(Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + position));
    }
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + position));
}

void Level::addHorizontalHall(int length, const Position &position) {
    Size size{3, length};

    for (auto row = 0; row < size.getRows(); row++) {
        deleteObjectAt(position + Position(row, 0));
        deleteObjectAt(position + Position(row, size.getCols() - 1));
    }

    putObject(Wall(Wall::CORNER, Position(0, 0) + position));
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    for (auto col = 1; col < size.getCols() - 1; col++) {
        putObject(Wall(Wall::HORIZONTAL, Position(0, col) + position));
        putObject(Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + position));
    }
    putObject(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, length - 1) + position));
}

void Level::addVerticalHall(int length, const Position &position) {
    Size size{length, 3};

    for (auto col = 0; col < size.getCols(); col++) {
        deleteObjectAt(position + Position(0, col));
        deleteObjectAt(position + Position(size.getRows() - 1, col));
    }

    putObject(Wall(Wall::CORNER, Position(0, 0) + position));
    putObject(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));
    for (auto row = 1; row < size.getRows() - 1; row++) {
        putObject(Wall(Wall::VERTICAL, Position(row, 0) + position));
        putObject(Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + position));
    }
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + position));
}

void Level::addGoal(const Position &position) {
    putObject(Goal(position));
}

void Level::addObstacle(const Position &position) {
    putObject(Obstacle(position));
}

void Level::addKey(const Position &position) {
    putObject(Key(position));
}

void Level::addDoor(const Position &position) {
    putObject(Door(position));
}

void Level::addCoin(const Position &position, int value) {
    putObject(Coin(position, value));
}

Position Level::addBlueprint(const std::string &level, int width = 80) {
    int row = 0;
    int col = 0;
    Position playerPosition{1, 1};
    for (char c: level) {
        switch (c) {
            case '+':
                putObject(Wall(Wall::CORNER, Position(row, col)));
                break;
            case '=':
                putObject(Wall(Wall::HORIZONTAL, Position(row, col)));
                break;
            case '|':
                putObject(Wall(Wall::VERTICAL, Position(row, col)));
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
