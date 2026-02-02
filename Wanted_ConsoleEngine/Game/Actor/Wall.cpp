#include "Wall.h"

Wall::Wall(const vec2& position) : super('#', position, Color::White)
{
    sortingOrder = 0;
}
