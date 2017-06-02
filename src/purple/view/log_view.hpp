#pragma once

#include "view.hpp"

class LogView : public View {
public:
    void onActorSpawn(std::shared_ptr<Actor> actor) override;
    void onTilesLoaded(const TileMap& tileMap) override;

    void update(double deltaSec) override {};
    void render() override {};
};