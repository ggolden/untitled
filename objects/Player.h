#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include <memory>
#include <vector>
#include "../Position.h"
//#include "Terminal.h"
#include "Object.h"
#include "Coin.h"

class Player : public Object {
    int levelIndex = 0;
    std::vector<std::unique_ptr<Object>> inventory;
    int coins = 0;

public:
    Player(int startingLevelIndex, const Position &startingPosition);

    int getLevelIndex() const;

    void setLevelIndex(int levelIndex);

    bool didWin() const;

    void setWon(bool won);

    void addToInventory(std::unique_ptr<Object>& object);

    void addToCoins(int value);

    int getCoins() const;

    bool hasInInventory(ObjectType objectType);

private:
    bool won = false;
};

#endif //UNTITLED_PLAYER_H
