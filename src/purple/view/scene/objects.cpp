#include "objects.hpp"

SceneGraphics::SceneGraphics(
    std::shared_ptr<PositionComponent> position,
    std::unique_ptr<Graphics>&& graphics)
    : _position(position)
    , _graphics(std::move(graphics))
{ }

void SceneGraphics::render(
    Canvas& canvas, const WorldPoint& cameraPosition) const
{
    ScreenOffset screenTopLeft =
        worldToScreenOffset(cameraPosition) - canvas.middle();
    WorldOffset worldOffset = _position->position - cameraPosition;
    ScreenOffset screenOffset = worldToScreenOffset(worldOffset);
    ScreenPoint screenPosition = canvas.middle() + screenOffset;
    _graphics->render(canvas, screenPosition);
}

void SceneGraphics::update(double deltaSec)
{
    _graphics->update(deltaSec);
}
