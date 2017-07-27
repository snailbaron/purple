#pragma once

#include "../renderer.hpp"
#include "../visual.hpp"

#include <purple/core/component.hpp>

class SceneObject {
public:
    virtual void render(
        Renderer& canvas, const WorldPoint& cameraPosition) const = 0;
    virtual void update(double deltaSec) {}
};

class SceneGraphics : public SceneObject {
public:
    SceneGraphics(
        std::shared_ptr<PositionComponent> position,
        std::unique_ptr<Visual>&& graphics);

    void render(
        Renderer& canvas, const WorldPoint& cameraPosition) const override;
    void update(double deltaSec) override;

private:
    std::shared_ptr<PositionComponent> _position;
    std::unique_ptr<Visual> _graphics;
};

