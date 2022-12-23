#include <cstdlib>
#include <iostream>
#include "Rando.h"

Rando::Rando(const Position &position) : ActiveObject('R', position, ObjectType::RANDO) {}

void Rando::act(Player &player) {
    Position newPosition = adjustedPosition();
    std::cout << "BOO" << std::endl;
    setPosition(newPosition);
}

Position Rando::adjustedPosition() const {
    int direction = rand() % 4;
    switch (direction) {
        case 0: return getPosition() + Position {1, 0};
        case 1: return getPosition() + Position {-1, 0};
        case 2: return getPosition() + Position {0, 1};
        default: return getPosition() + Position {0, -1};
    }
}
