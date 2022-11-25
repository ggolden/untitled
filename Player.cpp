#include "Player.h"

Player::Player() {}

char Player::getDisplayChar() const {
    return displayChar;
}

const Position &Player::getPosition() const {
    return position;
}

void Player::setPosition(const Position &newPosition) {
    position = newPosition;
}

int Player::getLevelIndex() const {
    return levelIndex;
}

void Player::setLevelIndex(int levelIndex) {
    Player::levelIndex = levelIndex;
}

void Player::display(Terminal &terminal) {
    terminal.display(getDisplayChar(), getPosition());
}
