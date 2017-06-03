#include "player_view.hpp"
#include <algorithm>
#include <utility>

namespace {

Color BACKGROUND_COLOR { 100, 100, 100 };

}

PlayerView::PlayerView()
    : _canvas()
{
}

bool PlayerView::processInput()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            return false;
        } else if (evt.type == SDL_MOUSEBUTTONDOWN &&
                evt.button.button == SDL_BUTTON_RIGHT) {
            auto controller = _controller.lock();
            if (controller) {
                auto input = motionInput(evt.button.x, evt.button.y);
                controller->setInput(input.x, input.y);
            }
        } else if (
                evt.type == SDL_MOUSEBUTTONUP &&
                evt.button.button == SDL_BUTTON_RIGHT) {
            auto controller = _controller.lock();
            if (controller) {
                controller->setInput(0, 0);
            }
        } else if (
                evt.type == SDL_MOUSEMOTION &&
                (evt.motion.state & SDL_BUTTON_RMASK)) {
            auto controller = _controller.lock();
            if (controller) {
                auto input = motionInput(evt.motion.x, evt.motion.y);
                controller->setInput(input.x, input.y);
            }
        }
    }

    return true;
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
        _scene.positionCamera(position);
    } else if (position && graphics) {
        auto graphicsResource = _resources.graphics(graphics->graphics);
        auto graphics = graphicsResource->createGraphics();
        _scene.placeSceneObject(position, std::move(graphics));
    }
}

void PlayerView::onTilesLoaded(const TileMap& tileMap)
{
    _scene.setTiles(_resources, tileMap);
}

void PlayerView::onControllerSpawn(
    std::shared_ptr<ControllerComponent> controller)
{
    _controller = controller;
}

Vector<double> PlayerView::motionInput(int mouseX, int mouseY) const
{
    Vector<double> offset = {
        1.0 * mouseX - _canvas.middle().x,
        1.0 * mouseY - _canvas.middle().y };
    return normalized(offset);
}