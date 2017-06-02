#include "scene.hpp"
#include "../core/geometry.hpp"
#include "canvas.hpp"
#include "resources.hpp"
#include <string>
#include <cmath>
#include <algorithm>

SceneSprite::SceneSprite(
        std::shared_ptr<BitmapResource> bitmap,
        const WorldPoint& position)
    : _bitmap(bitmap)
    , _position(position)
{ }

const WorldPoint& SceneSprite::position() const
{
    return _position;
}

void SceneSprite::render(Canvas& canvas, const ScreenPoint& screenPosition) const
{
    canvas.drawTexture(
        _bitmap->texture,
        SDL_Rect{0, 0, _bitmap->width, _bitmap->height},
        SDL_Rect{
            screenPosition.x, screenPosition.y,
            _bitmap->width, _bitmap->height});
}

SceneAnimation::SceneAnimation(
        std::shared_ptr<AnimationResource> animation,
        const WorldPoint& position,
        int fps)
    : _animation(animation)
    , _secondsPerFrame(1.0 / fps)
    , _position(position)
    , _playTime(0.0)
{ }

const WorldPoint& SceneAnimation::position() const
{
    return _position;
}

void SceneAnimation::render(
    Canvas& canvas, const ScreenPoint& screenPosition) const
{
    int frame = static_cast<int>(_playTime / _secondsPerFrame);

    SDL_Rect source {
        frame * _animation->frameWidth,
        0,
        _animation->frameWidth,
        _animation->frameHeight };

    SDL_Rect target {
        screenPosition.x,
        screenPosition.y,
        _animation->frameWidth,
        _animation->frameHeight };

    canvas.drawTexture(_animation->texture, source, target);
}

void SceneAnimation::update(double deltaSec)
{
    _playTime = std::fmod(
        _playTime + deltaSec, _secondsPerFrame * _animation->frameCount);
}

void SceneTiles::loadTiles(
        const ResourceStorage& resources, const TileMap& tileMap)
{
    _width = tileMap.width();
    _height = tileMap.height();
    _tileBitmaps.reserve(_width * _height);
    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            auto bitmapResource =
                std::static_pointer_cast<BitmapResource, Resource>(
                    resources.graphics(tileMap.tile(x, y).graphics));
            _tileBitmaps.push_back(bitmapResource);
        }
    }
}

void SceneTiles::render(Canvas& canvas, const ScreenOffset& screenOffset) const
{
    // TODO: Just rewrite this.

    int screenStartX = screenOffset.x;
    int screenStartY = screenOffset.y;
    int screenEndX = screenOffset.x + canvas.size().x - 1;
    int screenEndY = screenOffset.y + canvas.size().y - 1;

    int tileStartX = screenStartX / _tileSize.x;
    int tileStartY = screenStartY / _tileSize.y;
    int tileEndX = screenEndX / _tileSize.x;
    int tileEndY = screenEndY / _tileSize.y;

    int bitmapStartX = tileStartX * _tileSize.x - screenStartX;
    int bitmapStartY = tileStartY * _tileSize.y - screenStartY;

    int activeTileStartX = std::max(0, tileStartX);
    int activeTileStartY = std::max(0, tileStartY);
    int activeTileEndX = std::min((int)_width - 1, tileEndX);
    int activeTileEndY = std::min((int)_height - 1, tileEndY);

    for (int y = activeTileStartY; y <= activeTileEndY; y++) {
        for (int x = activeTileStartX; x <= activeTileEndX; x++) {
            auto texture = _tileBitmaps[y * _height + x]->texture;

            int xOffset = x - tileStartX;
            int yOffset = y - tileStartY;
            
            int bitmapX = bitmapStartX + xOffset * _tileSize.x;
            int bitmapY = bitmapStartY + yOffset * _tileSize.y;

            canvas.drawTexture(
                texture,
                {0, 0, _tileSize.x, _tileSize.y},
                {bitmapX, bitmapY, _tileSize.x, _tileSize.y});
        }
    }
}

void Scene::positionCamera(const WorldPoint& position)
{
    _cameraPosition = position;
}

void Scene::update(double deltaSec)
{
    for (auto& object : _objects) {
        object->update(deltaSec);
    }
}

void Scene::render(Canvas& canvas) const
{
    ScreenOffset screenTopLeft =
        worldToScreenOffset(_cameraPosition) - canvas.middle();
    _tileLayer.render(canvas, screenTopLeft);

    for (const auto& object : _objects) {
        WorldOffset worldOffset = object->position() - _cameraPosition;
        ScreenOffset screenOffset = worldToScreenOffset(worldOffset);
        ScreenPoint screenPosition = canvas.middle() + screenOffset;
        object->render(canvas, screenPosition);
    }
}

void Scene::placeGraphics(
    const WorldPoint& position, std::shared_ptr<Resource> resource)
{
    if (resource->type == ResourceType::Bitmap) {
        auto bitmapResource =
            std::static_pointer_cast<BitmapResource, Resource>(resource);
        _objects.push_back(std::make_unique<SceneSprite>(
            bitmapResource, position));
    } else if (resource->type == ResourceType::Animation) {
        auto animationResource =
            std::static_pointer_cast<AnimationResource, Resource>(resource);
        _objects.push_back(std::make_unique<SceneAnimation>(
            animationResource, position));
    }
}

void Scene::setTiles(const ResourceStorage& resources, const TileMap& tileMap)
{
    _tileLayer.loadTiles(resources, tileMap);
}