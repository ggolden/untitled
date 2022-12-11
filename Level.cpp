#include "Level.h"
#include "objects/Object.h"
#include "objects/ObjectType.h"
#include "objects/Goal.h"
#include "objects/Obstacle.h"
#include "objects/Wall.h"

void Level::putObject(const Object &object) {
    objects.push_back(object);
}

const std::string &Level::getName() const {
    return name;
}

void Level::display(Terminal &terminal) const {
    for (Object object: objects) {
        object.display(terminal);
    }
}

Object Level::getObjectAt(const Position &position) const {
    for (Object object: objects) {
        if (object.getPosition() == position) {
            return object;
        }
    }

    return {' ', position, ObjectType::SPACE};
}

void Level::deleteObjectAt(const Position &position) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects.at(i).getPosition() == position) {
            objects.erase(objects.begin() + i);
            break;
        }
    }
}

void Level::addRoom(const Size &size, const Position &position) {
    putObject(Wall(Wall::CORNER, Position(0, 0) + position));
    for (int col = 1; col < size.getCols() - 1; col++) {
        putObject(Wall(Wall::HORIZONTAL, Position(0, col) + position));
    }
    putObject(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));

    for (int row = 1; row < size.getRows() - 1; row++) {
        putObject(Wall(Wall::VERTICAL, Position(row, 0) + position));
        putObject(Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + position));
    }

    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    for (int col = 1; col < size.getCols() - 1; col++) {
        putObject(Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + position));
    }
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + position));
}

void Level::addHorizontalHall(int length, const Position &position) {
    Size size{3, length};

    for (int row = 0; row < size.getRows(); row++) {
        deleteObjectAt(position + Position(row, 0));
        deleteObjectAt(position + Position(row, size.getCols() - 1));
    }

    putObject(Wall(Wall::CORNER, Position(0, 0) + position));
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    for (int col = 1; col < size.getCols() - 1; col++) {
        putObject(Wall(Wall::HORIZONTAL, Position(0, col) + position));
        putObject(Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + position));
    }
    putObject(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, length - 1) + position));
}

void Level::addVerticalHall(int length, const Position &position) {
    Size size{length, 3};

    for (int col = 0; col < size.getCols(); col++) {
        deleteObjectAt(position + Position(0, col));
        deleteObjectAt(position + Position(size.getRows() - 1, col));
    }

    putObject(Wall(Wall::CORNER, Position(0, 0) + position));
    putObject(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + position));
    for (int row = 1; row < size.getRows() - 1; row++) {
        putObject(Wall(Wall::VERTICAL, Position(row, 0) + position));
        putObject(Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + position));
    }
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + position));
    putObject(Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + position));
}

void Level::addObstacle(const Position &position) {
    putObject(Obstacle(position));
}

void Level::addGoal(const Position &position) {
    putObject(Goal(position));
}

Level::Level(const std::string &name) : name(name) {

}

