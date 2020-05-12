#include <deque>
#include "./coordinate.h"


class Snake {
public:
    void init(const std::deque<Coordinate>& coords);
    void move(Direction direction, bool removeBack = true);

    void add(const Coordinate& coord);
    void add(int x, int y, int z) { add({x, y, z}); };

    const Coordinate& head() const { return coords.front(); }
    int headX() const { return coords.front().x; }
    int headY() const { return coords.front().y; }
    int headZ() const { return coords.front().z; }

private:
    std::deque<Coordinate> coords;
};
