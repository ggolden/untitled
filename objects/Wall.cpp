#include <curses.h>
#include "Wall.h"

Wall::Wall(WallType type, const Position &position) : Object(type, position, ObjectType::WALL) {}
