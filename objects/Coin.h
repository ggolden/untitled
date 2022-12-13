#ifndef UNTITLED_COIN_H
#define UNTITLED_COIN_H

#include "Object.h"

class Coin : public Object {
    int amount;

public:
    Coin(const Position &position, int amount);
    ~Coin() override = default;

    int getAmount() const;
};

#endif //UNTITLED_COIN_H
