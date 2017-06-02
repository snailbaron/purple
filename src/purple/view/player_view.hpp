#pragma once

#include "view.hpp"
#include "canvas.hpp"
#include "resources.hpp"
#include "scene.hpp"
#include "../core/tile_map.h"
#include <map>
#include <memory>
#include <unordered_map>

class PlayerView : public View {
public:
    PlayerView();

    // Notifications from game core
    void onActorSpawn(std::shared_ptr<Actor> actor) override;
    void onTilesLoaded(const TileMap& tileMap) override;
    void onControllerSpawn(
        std::shared_ptr<ControllerComponent> controller) override;

    // User input
    bool processInput();

    void loadResources();

    void update(double deltaSec) override;
    void render() override;

private:
    Vector<double> motionInput(int mouseX, int mouseY) const;

    Canvas _canvas;
    ResourceStorage _resources;
    Scene _scene;
    std::weak_ptr<ControllerComponent> _controller;
};