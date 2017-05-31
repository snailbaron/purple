#include "scene.hpp"
#include "../core/geometry.hpp"
#include "canvas.hpp"
#include "resources.hpp"
#include <string>
#include <cmath>

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