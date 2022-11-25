#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include "Position.h"
#include "Terminal.h"

class Player {
    char displayChar = '@';
    int levelIndex = 0;
    Position position{0, 0};

public:
    Player();

    char getDisplayChar() const;

    const Position &getPosition() const;

    int getLevelIndex() const;

    void setLevelIndex(int levelIndex);

    void display(Terminal &terminal);
};

#endif //UNTITLED_PLAYER_H
