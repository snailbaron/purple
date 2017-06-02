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

    void onActorSpawn(std::shared_ptr<Actor> actor) override;
    void onTilesLoaded(const TileMap& tileMap) override;

    void loadResources();

    void update(double deltaSec) override;
    void render() override;

private:
    Canvas _canvas;
    ResourceStorage _resources;
    Scene _scene;
};