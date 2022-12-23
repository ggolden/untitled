#ifndef UNTITLED_RANDO_H
#define UNTITLED_RANDO_H

#include "ActiveObject.h"

class Rando : public ActiveObject {
    Position adjustedPosition() const;

public:
    Rando(const Position &position);

    void act(Player &player) override;
};

#endif //UNTITLED_RANDO_H
