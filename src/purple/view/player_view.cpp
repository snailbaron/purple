#include "player_view.hpp"
#include "layouts/main_menu_layout.hpp"
#include "geometry.hpp"
#include <algorithm>
#include <utility>

namespace {

Color BACKGROUND_COLOR { 100, 100, 100 };

}

Terminal::Terminal()
    : _canvas()
{ }

void Terminal::listen(const GameStartedEvent&)
{
    _widgets.contents({
        std::make_unique<MenuButton>(
            ScreenPosition({0.5_frac, 0.3_frac}),
            "New Game",
            [this] {
                _game.request(NewGameRequest{});
            })
    });
}

void Terminal::attachTo(Game& game)
{
    _game = game;
    _game.attach(this);
}

// TODO: Subscribe controller directly to input? Should be nice.

void Terminal::listen(const input::ButtonEvent& buttonEvent)
{
    if (buttonEvent.button == input::MenuButton::MouseRight) {
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

void Terminal::listen(const input::PointerMotionEvent& event)
{
    if (_controllerStateDown) {
        auto controller = _controller.lock();
        if (controller) {
            auto input = motionInput(event.x, event.y);
            controller->setInput(input.x, input.y);
        }
    }
}

void Terminal::subscribeToInput(input::InputManager& inputManager)
{
    inputManager.subscribe<input::ButtonEvent>(this);
    inputManager.subscribe<input::PointerMotionEvent>(this);
}

void Terminal::loadResources()
{
    _resources.loadGraphics(_canvas, "../../assets");
}

void Terminal::update(double deltaSec)
{
    _scene.update(deltaSec);
}

void Terminal::render()
{
    _canvas.clear(BACKGROUND_COLOR);
    //_scene.render(_renderer);





    _canvas.present();
}

//
// Handlers to notifications from game core
//

void Terminal::onActorSpawn(std::shared_ptr<Actor> actor)
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

void Terminal::onTilesLoaded(const TileMap& tileMap)
{
    _scene.setTiles(_resources, tileMap);
}

void Terminal::onControllerSpawn(
    std::shared_ptr<ControllerComponent> controller)
{
    _controller = controller;
}

Vector<double> Terminal::motionInput(int mouseX, int mouseY) const
{
    ScreenPoint rendererMiddle {
        _canvas.size().width / 2, _canvas.size().height / 2};

    Vector<double> offset = {
        1.0 * mouseX - rendererMiddle.x,
        1.0 * mouseY - rendererMiddle.y };
    return normalized(offset);
}