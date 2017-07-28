#include "player_view.hpp"
#include <algorithm>
#include <utility>

namespace {

Color BACKGROUND_COLOR { 100, 100, 100 };

}

PlayerView::PlayerView()
    : _renderer()
{
}

// TODO: Subscribe controller directly to input? Should be nice.

void PlayerView::listen(const input::ButtonEvent& buttonEvent)
{
    if (buttonEvent.button == input::Button::MouseRight) {
        auto controller = _controller.lock();
        if (controller) {
            if (buttonEvent.action == input::ButtonEvent::Action::Press) {
                auto input = motionInput(buttonEvent.x, buttonEvent.y);
                controller->setInput(input.x, input.y);
                _controllerStateDown = true;
            } else {
                controller->setInput(0, 0);
                _controllerStateDown = false;
            }
        }
    }
}

void PlayerView::listen(const input::PointerMotionEvent& event)
{
    if (_controllerStateDown) {
        auto controller = _controller.lock();
        if (controller) {
            auto input = motionInput(event.x, event.y);
            controller->setInput(input.x, input.y);
        }
    }
}

void PlayerView::subscribeToInput(input::InputManager& inputManager)
{
    inputManager.subscribe<input::ButtonEvent>(this);
    inputManager.subscribe<input::PointerMotionEvent>(this);
}

void PlayerView::loadResources()
{
    _resources.loadGraphics(_renderer, "../../assets");
}

void PlayerView::update(double deltaSec)
{
    _scene.update(deltaSec);
}

void PlayerView::render()
{
    _renderer.clear(BACKGROUND_COLOR);
    _scene.render(_renderer);
    _renderer.present();
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
    ScreenPoint rendererMiddle {
        _renderer.size().width / 2, _renderer.size().height / 2};

    Vector<double> offset = {
        1.0 * mouseX - rendererMiddle.x,
        1.0 * mouseY - rendererMiddle.y };
    return normalized(offset);
}