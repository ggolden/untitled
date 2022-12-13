#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include <vector>
#include "../Position.h"
//#include "Terminal.h"
#include "Object.h"

class Player : public Object {
    int levelIndex = 0;
    std::vector<Object> inventory;

public:
    Player(int startingLevelIndex, const Position &startingPosition);

    int getLevelIndex() const;

    void setLevelIndex(int levelIndex);

    bool didWin() const;

    void setWon(bool won);

    void addToInventory(const Object& object);

    bool hasInIventory(ObjectType objectType);

private:
    bool won = false;
};

#endif //UNTITLED_PLAYER_H
