#include "tile_level.h"
#include <stdexcept>
#include <sstream>

TileLevel::TileLevel(int width, int height)
    : _width(width)
    , _height(height)
{
    _tiles.resize(width * height);
}

void TileLevel::size(int width, int height)
{
    _width = width;
    _height = height;
    _tiles.resize(width * height);
}

const Tile& TileLevel::tile(int x, int y) const
{
    int index = y * _width + x;
    if (index < 0 || index >= _width * _height) {
        std::ostringstream ss;
        ss << "TileLevel: no tile with coordinates: " << x << ", " << y;
        throw std::runtime_error(ss.str());
    }

    return _tiles[index];
}