#pragma once

#include "view.hpp"
#include "renderer.hpp"
#include "resources.hpp"
#include "scene/scene.hpp"
#include "purple/core/tile_map.h"
#include <purple/input/input.hpp>
#include <map>
#include <memory>
#include <unordered_map>

class PlayerView
    : public View
    , public Listener<input::ButtonEvent>
    , public Listener<input::PointerMotionEvent> {
public:
    PlayerView();

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
    void listen(const input::ButtonEvent& buttonEvent) override;
    void listen(const input::PointerMotionEvent& pointerMotionEvent) override;

    Vector<double> motionInput(int mouseX, int mouseY) const;

    Renderer _renderer;
    ResourceStorage _resources;
    Scene _scene;
    std::weak_ptr<ControllerComponent> _controller;
    bool _controllerStateDown = false;
};