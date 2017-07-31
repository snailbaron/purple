#include "objects.hpp"

SceneGraphics::SceneGraphics(
    std::shared_ptr<PositionComponent> position,
    std::unique_ptr<Visual>&& graphics)
    : _position(position)
    , _graphics(std::move(graphics))
{ }

void SceneGraphics::render(
    Canvas& renderer, const WorldPoint& cameraPosition) const
{
    ScreenPoint rendererMiddle(
        renderer.size().width / 2,
        renderer.size().height / 2);

    ScreenOffset screenTopLeft =
        worldToScreenOffset(cameraPosition) - rendererMiddle;
    WorldOffset worldOffset = _position->position - cameraPosition;
    ScreenOffset screenOffset = worldToScreenOffset(worldOffset);
    ScreenPoint screenPosition = rendererMiddle + screenOffset;
    _graphics->render(renderer, screenPosition);
}

void SceneGraphics::update(double deltaSec)
{
    _graphics->update(deltaSec);
}
