#include "Coin.h"

Coin::Coin(const Position &position, int amount) : Object('o', position, ObjectType::COIN), amount(amount) {}

int Coin::getAmount() const {
    return amount;
}
