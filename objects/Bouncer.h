#ifndef UNTITLED_BOUNCER_H
#define UNTITLED_BOUNCER_H

#include "ActiveObject.h"

class Bouncer : public ActiveObject {
public:
    explicit Bouncer(const Position &position);

    void act(Player &player) override;
};

#endif //UNTITLED_BOUNCER_H
