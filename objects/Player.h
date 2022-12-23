#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include <memory>
#include <vector>
#include <string>
#include "../Position.h"
#include "Object.h"
#include "Coin.h"

class Player : public Object {
    int levelIndex = 0;
    std::vector<std::unique_ptr<Object>> inventory;
    int coins = 0;
    bool alive = true;
    std::string message;

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

    void kill(std::string message);

    bool isAlive();

    std::string getMessage() const;

private:
    bool won = false;
};

#endif //UNTITLED_PLAYER_H
