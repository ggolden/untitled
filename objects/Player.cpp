#include "Player.h"

Player::Player(int startingLevelIndex, const Position &startingPosition) : //
        Object('@', startingPosition, ObjectType::PLAYER), //
        levelIndex(startingLevelIndex) {}

int Player::getLevelIndex() const {
    return levelIndex;
}

void Player::setLevelIndex(int levelIndex) {
    Player::levelIndex = levelIndex;
}

bool Player::didWin() const {
    return won;
}

void Player::setWon(bool won) {
    Player::won = won;
}

void Player::addToInventory(const Object &object) {
    inventory.push_back(object);
}

bool Player::hasInIventory(ObjectType objectType) {
    for (auto item: inventory) {
        if (item.getType() == objectType) {
            return true;
        }
    }

    return false;
}
