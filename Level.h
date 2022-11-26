#ifndef UNTITLED_LEVEL_H
#define UNTITLED_LEVEL_H

#include <string>
#include <vector>
#include "Size.h"
#include "Terminal.h"
#include "Player.h"
#include "Object.h"

class Level {
    std::string name;
    Size size;
    Position offset;
    std::vector<Object> objects;

    void init();
    void createWalls();
    void createGoal();

public:
    Level(std::string name, const Size &size, const Position &offset);

    const std::string &getName() const;

    const Position &getOffset() const;

    const Size &getSize() const;

    void display(Terminal &terminal) const;

    Object getObjectAt(const Position &position) const;
};

#endif //UNTITLED_LEVEL_H
