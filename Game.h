#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include <vector>
#include "Level.h"
#include "Terminal.h"
#include "Position.h"
#include "objects/Object.h"
#include "objects/Player.h"
#include "Command.h"

class Game {
    static std::string level0;
    static std::string level1;

    std::vector<Level> levels;
    Player player{0, Position(0, 0)};

    void init();

    static Command parse(int input);

    void movePlayerIfPossible(const Position &newPosition, const Object *objectAtPosition, Level& level);

    void processPlayerInteraction(const Object *objectAtPosition, Level& level);

    Position computeNewPlayerPosition(Command command);

    void showTitle(Terminal &terminal);

    void gameLoop(Terminal &terminal);

public:
    Game();

    void play(Terminal &terminal);

    void showEndScreen(Terminal &terminal);

};

#endif //UNTITLED_GAME_H
