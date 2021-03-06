#include "scene.hpp"
#include "purple/core/geometry.hpp"
#include <string>
#include <cmath>
#include <algorithm>

void SceneTiles::loadTiles(
        const ResourceStorage& resources, const TileMap& tileMap)
{
    _width = tileMap.width();
    _height = tileMap.height();
    _tileGraphics.reserve(_width * _height);
    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            auto resource = resources.graphics(tileMap.tile(x, y).graphics);
            std::unique_ptr<Visual> graphics = resource->createGraphics();
            _tileGraphics.push_back(std::move(graphics));
        }
    }
}

void SceneTiles::render(Renderer& renderer, const ScreenOffset& screenOffset) const
{
    // TODO: Just rewrite this.

    int screenStartX = screenOffset.x;
    int screenStartY = screenOffset.y;

    int screenEndX = screenOffset.x + renderer.size().width - 1;
    int screenEndY = screenOffset.y + renderer.size().height - 1;

    int tileStartX = screenStartX / _tileSize.x;
    int tileStartY = screenStartY / _tileSize.y;
    int tileEndX = screenEndX / _tileSize.x;
    int tileEndY = screenEndY / _tileSize.y;

    int bitmapStartX = tileStartX * _tileSize.x - screenStartX + _tileSize.x / 2;
    int bitmapStartY = tileStartY * _tileSize.y - screenStartY + _tileSize.y / 2;

    int activeTileStartX = std::max(0, tileStartX);
    int activeTileStartY = std::max(0, tileStartY);
    int activeTileEndX = std::min((int)_width - 1, tileEndX);
    int activeTileEndY = std::min((int)_height - 1, tileEndY);

    for (int y = activeTileStartY; y <= activeTileEndY; y++) {
        for (int x = activeTileStartX; x <= activeTileEndX; x++) {
            int xOffset = x - tileStartX;
            int yOffset = y - tileStartY;
            
            int bitmapX = bitmapStartX + xOffset * _tileSize.x;
            int bitmapY = bitmapStartY + yOffset * _tileSize.y;

            _tileGraphics[y * _height + x]->render(renderer, {bitmapX, bitmapY});
        }
    }
}

void Scene::positionCamera(std::shared_ptr<PositionComponent> cameraPosition)
{
    _cameraPosition = cameraPosition;
}

void Scene::update(double deltaSec)
{
    for (auto& object : _objects) {
        object->update(deltaSec);
    }
}

void Scene::render(Renderer& renderer) const
{
    ScreenPoint rendererMiddle(
        renderer.size().width / 2,
        renderer.size().height / 2);

    ScreenOffset screenTopLeft =
        worldToScreenOffset(_cameraPosition->position) - rendererMiddle;
    _tileLayer.render(renderer, screenTopLeft);

    for (const auto& object : _objects) {
        object->render(renderer, _cameraPosition->position);
    }
}

void Scene::placeSceneObject(
    std::shared_ptr<PositionComponent> position,
    std::unique_ptr<Visual>&& graphics)
{
    _objects.push_back(std::make_unique<SceneGraphics>(
        position, std::move(graphics)));
}

void Scene::setTiles(const ResourceStorage& resources, const TileMap& tileMap)
{
    _tileLayer.loadTiles(resources, tileMap);
}