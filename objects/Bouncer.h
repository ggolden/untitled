#ifndef UNTITLED_BOUNCER_H
#define UNTITLED_BOUNCER_H

#include "ActiveObject.h"
#include "../Level.h"

class Bouncer : public ActiveObject {
public:
    enum Direction {
        HORIZONTAL, VERTICAL
    };

    Bouncer(const Position &position, Direction direction);

    void act(Player &player, const Level &level) override;

private:
    Direction direction;
    bool forward = true;
    Position adjustedPosition() const;
};

#endif //UNTITLED_BOUNCER_H
