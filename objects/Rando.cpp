#include <cstdlib>
#include "Rando.h"

Rando::Rando(const Position &position) : ActiveObject('R', position, ObjectType::RANDO) {}

void Rando::act(Player &player, const Level &level) {
    Position newPosition = adjustedPosition();
    const Object * object = level.getObjectAt(newPosition);

    if (player.getPosition() == newPosition) {
        player.kill("Caught by the Rando!");
    }

    if (!object || (object->getType() != ObjectType::WALL && object->getType() != ObjectType::DOOR)) {
        setPosition(newPosition);
    }
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
