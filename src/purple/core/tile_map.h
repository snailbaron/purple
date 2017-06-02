#pragma once

#include <string>
#include <vector>
#include <initializer_list>
#include <stdexcept>

struct Tile {
    Tile(std::string graphics);
    std::string graphics;
};

class TileSet {
public:
    const Tile& tile(size_t i) const { return _tiles[i]; }
    size_t size() const { return _tiles.size(); }

    template <class Container = std::initializer_list<Tile>>
    void fill(const Container& tiles)
    {
        _tiles.clear();
        _tiles.reserve(tiles.size());
        for (const Tile& tile : tiles) {
            _tiles.push_back(tile);
        }
    }

private:
    std::vector<Tile> _tiles;
};

class TileMap {
public:
    TileMap(TileSet tileSet);

    size_t width() const { return _mapWidth; }
    size_t height() const { return _mapTiles.size() / _mapWidth; }

    template <class Container = std::initializer_list<size_t>>
    void fill(size_t width, size_t height, const Container& cells)
    {
        if (cells.size() != width * height) {
            throw std::runtime_error(
                "TileMap::fill: number of cells does not match size");
        }

        _mapWidth = width;
        _mapTiles.clear();
        _mapTiles.reserve(cells.size());
        for (size_t tileIndex : cells) {
            if (tileIndex >= _tileSet.size()) {
                throw std::runtime_error(
                    "TileMap::fill: cell index is not in tile set");
            }

            _mapTiles.push_back(tileIndex);
        }
    }

    const Tile& tile(size_t x, size_t y) const;

private:
    TileSet _tileSet;
    size_t _mapWidth;
    std::vector<size_t> _mapTiles;
};