#include "./snake.h"
#include "../driver/cube.h"

extern LedCube cube;


void Snake::init(const std::deque<Coordinate>& coords) {
    this->coords = coords;
    for (auto& coord : coords)
        cube(coord) = LED_ON;
}

void Snake::add(const Coordinate& coord) {
    if (coord.isValid()) {
        coords.push_front(coord);
        cube(coord) = LED_ON;
    }
}


void Snake::move(Direction direction, bool removeBack) {
    if (removeBack) {
        cube(coords.back()) = LED_OFF;
        coords.pop_back();
    }
    auto newCoord = coords.front().getOffset(direction, 1);
    if (newCoord.isValid())  {
        coords.push_front(newCoord);
        cube(coords.front()) = LED_ON;
    }
    cube.update();
}
