#pragma once

#include "resources.hpp"
#include <vector>
#include <string>
#include <memory>

class SceneObject {
public:
    virtual const WorldPoint& position() const = 0;
    virtual void render(Canvas& canvas, const ScreenPoint& screenPosition) const = 0;
    virtual void update(double deltaSec) {}
};

class SceneSprite : public SceneObject {
public:
    SceneSprite(
        std::shared_ptr<BitmapResource> bitmap,
        const WorldPoint& position);

    const WorldPoint& position() const override;
    void render(Canvas& canvas, const ScreenPoint& screenPosition) const override;

private:
    std::shared_ptr<BitmapResource> _bitmap;
    WorldPoint _position;
};

class SceneAnimation : public SceneObject {
public:
    SceneAnimation(
        std::shared_ptr<AnimationResource> animation,
        const WorldPoint& position,
        int fps = 3);

    const WorldPoint& position() const override;
    void render(Canvas& canvas, const ScreenPoint& screenPosition) const override;
    void update(double deltaSec) override;

private:
    std::shared_ptr<AnimationResource> _animation;
    double _secondsPerFrame;
    WorldPoint _position;
    double _playTime;
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
    void render(Canvas& canvas) const;
    void positionCamera(const WorldPoint& position);
    void placeGraphics(
        const WorldPoint& position, std::shared_ptr<Resource> resource);

private:
    WorldPoint _cameraPosition;
    std::vector<std::unique_ptr<SceneObject>> _objects;
};