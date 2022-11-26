#include "Level.h"
#include "Object.h"
#include "ObjectType.h"

Level::Level(std::string name, const Size &size, const Position &offset) : name(name), size(size), offset(offset) {
    init();
}

void Level::init() {
    createWalls();
}

void Level::createWalls() {
    objects.push_back(Object('+', Position(0,0), ObjectType::WALL));
    for (int col = 1; col < size.getCols()-1; col++) {
        objects.push_back(Object('=', Position(0, col), ObjectType::WALL));
    }
    objects.push_back(Object('+', Position(0,size.getCols()-1), ObjectType::WALL));

    for (int row = 1; row < size.getRows()-1; row++) {
        objects.push_back(Object('|', Position(row,0), ObjectType::WALL));
        objects.push_back(Object('|', Position(row,size.getCols()-1), ObjectType::WALL));
    }

    objects.push_back(Object('+', Position(size.getRows()-1,0), ObjectType::WALL));
    for (int col = 1; col < size.getCols()-1; col++) {
        objects.push_back(Object('=', Position(size.getRows()-1, col), ObjectType::WALL));
    }
    objects.push_back(Object('+', Position(size.getRows()-1,size.getCols()-1), ObjectType::WALL));
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
    for (Object object : objects) {
        object.display(terminal);
    }
}
