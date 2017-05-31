#pragma once

#include <string>
#include <vector>

struct Tile {
    std::string graphics;
};

class TileLevel {
public:
    TileLevel(int width, int height);

    void size(int width, int height);
    const Tile& tile(int x, int y) const;

private:
    int _width;
    int _height;
    std::vector<Tile> _tiles;
};