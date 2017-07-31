#pragma once

#include "view.hpp"
#include "canvas.hpp"
#include "resources.hpp"
#include "widget.hpp"
#include "scene/scene.hpp"
#include "purple/core/tile_map.h"
#include "../core/game.hpp"
#include <purple/input/input.hpp>
#include <map>
#include <vector>
#include <memory>
#include <unordered_map>

class Terminal
    : public View
    , public Listener<input::ButtonEvent>
    , public Listener<input::PointerMotionEvent>
    , public Listener<GameStartedEvent> {
public:
    Terminal();

    void attachTo(Game& game);

    // Notifications from game core
    void onActorSpawn(std::shared_ptr<Actor> actor) override;
    void onTilesLoaded(const TileMap& tileMap) override;
    void onControllerSpawn(
        std::shared_ptr<ControllerComponent> controller) override;

    void subscribeToInput(input::InputManager& inputManager);

    void loadResources();

    void update(double deltaSec) override;
    void render() override;

private:
    void listen(const GameStartedEvent&) override;
    void listen(const input::ButtonEvent& buttonEvent) override;
    void listen(const input::PointerMotionEvent& pointerMotionEvent) override;

    Vector<double> motionInput(int mouseX, int mouseY) const;

    WidgetPanel _widgets;
    Game& _game;
    Canvas _canvas;
    ResourceStorage _resources;
    Scene _scene;
    std::weak_ptr<ControllerComponent> _controller;
    bool _controllerStateDown = false;
};