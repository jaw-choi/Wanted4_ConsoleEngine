#include "Box.h"

Box::Box(const vec2& newPosition) : super('B', newPosition, Color::Blue)
{
    sortingOrder = 5;
}
