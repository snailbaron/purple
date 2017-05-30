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
    _resources.loadBitmaps();
    _resources.convertBitmapsToTextures(_canvas);
}

void PlayerView::update(double deltaSec)
{
}

void PlayerView::render()
{
    _canvas.clear(BACKGROUND_COLOR);
    for (const auto& drawable : _drawables) {
        _canvas.drawTexture(drawable.second);
    }

    _canvas.present();
}

//
// Handlers to notifications from game core
//

void PlayerView::onActorSpawn(std::shared_ptr<Actor> actor)
{
    if (actor->hasComponent(ComponentType::Position) &&
            actor->hasComponent(ComponentType::Graphics)) {
        auto position =
            actor->getComponent<ComponentType::Position>()->position;
        auto texture = _resources.texture(
            actor->getComponent<ComponentType::Graphics>()->graphics);
        _drawables[position] = texture;
    }
}