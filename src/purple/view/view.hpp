#pragma once

#include "../core/actor.hpp"
#include "../core/tile_map.h"
#include <memory>

class View {
public:
    // Notifications from Core
    virtual void onActorSpawn(std::shared_ptr<Actor> actor) {};
    virtual void onTilesLoaded(const TileMap& tileMap) {};

    // Mandatory View interface
    virtual void update(double deltaSec) = 0;
    virtual void render() = 0;
};