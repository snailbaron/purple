#include "player_view.hpp"

namespace {

Color BACKGROUND_COLOR { 100, 100, 100 };

}

PlayerView::PlayerView()
    : _canvas()
{
}

void PlayerView::loadResources()
{
    _resources.loadGraphics(_canvas, "../../assets");
}

void PlayerView::update(double deltaSec)
{
    _scene.update(deltaSec);
}

void PlayerView::render()
{
    _canvas.clear(BACKGROUND_COLOR);
    _scene.render(_canvas);
    _canvas.present();
}

//
// Handlers to notifications from game core
//

void PlayerView::onActorSpawn(std::shared_ptr<Actor> actor)
{
    auto position = actor->get<PositionComponent>();
    auto graphics = actor->get<GraphicsComponent>();
    auto camera = actor->get<CameraComponent>();

    if (position && camera) {
        _scene.positionCamera(position->position);
    } else if (position && graphics) {
        _scene.placeGraphics(
            position->position, _resources.graphics(graphics->graphics)); // <-- madness, do something about it
    }
}

void PlayerView::onTilesLoaded(const TileMap& tileMap)
{
    _scene.setTiles(_resources, tileMap);
}