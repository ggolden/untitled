#include "Room.h"
#import "objects/Wall.h"

Room::Room(const Size &size, const Position &offset) : size(size), offset(offset) {}

void Room::init(std::vector<Object> &objects) {
    addWalls(objects);
};

void Room::addWalls(std::vector<Object> &objects) {
    objects.push_back(Wall(Wall::CORNER, Position(0, 0) + offset));
    for (int col = 1; col < size.getCols() - 1; col++) {
        objects.push_back(Wall(Wall::HORIZONTAL, Position(0, col) + offset));
    }
    objects.push_back(Wall(Wall::CORNER, Position(0, size.getCols() - 1) + offset));

    for (int row = 1; row < size.getRows() - 1; row++) {
        objects.push_back(Wall(Wall::VERTICAL, Position(row, 0) + offset));
        objects.push_back(Wall(Wall::VERTICAL, Position(row, size.getCols() - 1) + offset));
    }

    objects.push_back(Wall(Wall::CORNER, Position(size.getRows() - 1, 0) + offset));
    for (int col = 1; col < size.getCols() - 1; col++) {
        objects.push_back(Wall(Wall::HORIZONTAL, Position(size.getRows() - 1, col) + offset));
    }
    objects.push_back(Wall(Wall::CORNER, Position(size.getRows() - 1, size.getCols() - 1) + offset));
}
