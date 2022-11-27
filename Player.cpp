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
