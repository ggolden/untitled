#include "Level.h"
#include "Room.h"
#include "objects/Object.h"
#include "objects/ObjectType.h"
#include "objects/Goal.h"

Level::Level(std::string name) : name(name) {
    init();
}

void Level::init() {
    createRooms();
    createGoal();
}

void Level::createRooms() {
    Room room1{Size(9, 14), Position(0, 0)};
    room1.init(objects);
    rooms.push_back(room1);

    Room room2{Size(9, 14), Position(3, 14)};
    room2.init(objects);
    rooms.push_back(room2);

}

void Level::createGoal() {
    objects.push_back(Goal(Position(3, 3)));
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
