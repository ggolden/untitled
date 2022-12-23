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

void Player::addToInventory(std::unique_ptr<Object> &object) {
    inventory.push_back(std::move(object));
}

bool Player::hasInInventory(ObjectType objectType) {
    for (auto &item: inventory) {
        if (item->getType() == objectType) {
            return true;
        }
    }

    return false;
}

void Player::addToCoins(int value) {
    coins += value;
}

int Player::getCoins() const {
    return coins;
}

void Player::kill(std::string message) {
    alive = false;
    Player::message = message;
}

bool Player::isAlive() {
    return alive;
}

std::string Player::getMessage() const {
    return message;
}
