#include <purple/core/tile_map.h>
#include <stdexcept>
#include <sstream>
#include <utility>

Tile::Tile(std::string graphics)
    : graphics(std::move(graphics))
{ }

TileMap::TileMap(TileSet tileSet)
    : _tileSet(std::move(tileSet))
{ }

const Tile& TileMap::tile(size_t x, size_t y) const
{
    size_t index = y * _mapWidth + x;
    if (index >= _mapTiles.size()) {
        std::ostringstream ss;
        ss << "TileLevel: no tile with coordinates: " << x << ", " << y;
        throw std::runtime_error(ss.str());
    }

    return _tileSet.tile(_mapTiles[index]);
}