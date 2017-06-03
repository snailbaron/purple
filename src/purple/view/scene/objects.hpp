#pragma once

#include "../canvas/canvas.hpp"
#include "../canvas/graphics.hpp"
#include "../../core/component.hpp"

class SceneObject {
public:
    virtual void render(
        Canvas& canvas, const WorldPoint& cameraPosition) const = 0;
    virtual void update(double deltaSec) {}
};

class SceneGraphics : public SceneObject {
public:
    SceneGraphics(
        std::shared_ptr<PositionComponent> position,
        std::unique_ptr<Graphics>&& graphics);

    void render(
        Canvas& canvas, const WorldPoint& cameraPosition) const override;
    void update(double deltaSec) override;

private:
    std::shared_ptr<PositionComponent> _position;
    std::unique_ptr<Graphics> _graphics;
};

