#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include "../Position.h"
//#include "Terminal.h"
#include "Object.h"

class Player : public Object {
    int levelIndex = 0;

public:
    Player(int startingLevelIndex, const Position &startingPosition);

    int getLevelIndex() const;

    void setLevelIndex(int levelIndex);
};

#endif //UNTITLED_PLAYER_H
