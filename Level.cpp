#include "Level.h"
#include "Object.h"
#include "Wall.h"
#include "ObjectType.h"
#include "Goal.h"

Level::Level(std::string name, const Size &size, const Position &offset) : name(name), size(size), offset(offset) {
    init();
}

void Level::init() {
    createWalls();
    createGoal();
}

void Level::createWalls() {
    objects.push_back(Wall(Wall::WallType::CORNER, Position(0, 0)));
    for (int col = 1; col < size.getCols() - 1; col++) {
        objects.push_back(Wall(Wall::WallType::HORIZONTAL, Position(0, col)));
    }
    objects.push_back(Wall(Wall::WallType::CORNER, Position(0, size.getCols() - 1)));

    for (int row = 1; row < size.getRows() - 1; row++) {
        objects.push_back(Wall(Wall::WallType::VERTICAL, Position(row, 0)));
        objects.push_back(Wall(Wall::WallType::VERTICAL, Position(row, size.getCols() - 1)));
    }

    objects.push_back(Wall(Wall::WallType::CORNER, Position(size.getRows() - 1, 0)));
    for (int col = 1; col < size.getCols() - 1; col++) {
        objects.push_back(Wall(Wall::WallType::HORIZONTAL, Position(size.getRows() - 1, col)));
    }
    objects.push_back(Wall(Wall::WallType::CORNER, Position(size.getRows() - 1, size.getCols() - 1)));
}

void Level::createGoal() {
    objects.push_back(Goal(Position(size.getRows() - 2, size.getCols() - 2)));
}

const std::string &Level::getName() const {
    return name;
}

const Position &Level::getOffset() const {
    return offset;
}

const Size &Level::getSize() const {
    return size;
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

    return Object(' ', position, ObjectType::SPACE);
}
