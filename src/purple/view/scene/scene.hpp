#pragma once

#include "objects.hpp"
#include "../resources.hpp"

#include <purple/core/tile_map.h>
#include <purple/core/component.hpp>

#include <vector>
#include <string>
#include <memory>

class SceneTiles {
public:
    void loadTiles(const ResourceStorage& resources, const TileMap& tileMap);
    void render(Renderer& canvas, const ScreenOffset& screenOffset) const;

private:
    size_t _width;
    size_t _height;
    ScreenSize _tileSize {64, 64};
    std::vector<std::unique_ptr<Visual>> _tileGraphics;
};

/**
 * Scene holds all drawable objects to be displayed on screen. Its primary task
 * is to forward drawing requests to the contained objects.
 *
 * The Scene may implement additional optimizations, considering which objects
 * should be considered for drawing. Currently, this is not implemented.
 */
class Scene {
public:
    void update(double deltaSec);
    void render(Renderer& canvas) const;

    void positionCamera(std::shared_ptr<PositionComponent> cameraPosition);
    void setTiles(const ResourceStorage& resources, const TileMap& tileMap);

    void placeSceneObject(
        std::shared_ptr<PositionComponent> position,
        std::unique_ptr<Visual>&& graphics);

private:
    using SceneObjectVector = std::vector<std::unique_ptr<SceneObject>>;

    std::shared_ptr<PositionComponent> _cameraPosition;
    SceneTiles _tileLayer;
    SceneObjectVector _objects;
    std::map<std::weak_ptr<Actor>, SceneObjectVector::iterator> _actorMap;
};