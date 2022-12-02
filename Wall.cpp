#include <curses.h>
#include "Wall.h"

Wall::Wall(WallType type, const Position &position) : Object(ACS_CKBOARD, position, ObjectType::WALL) {}
