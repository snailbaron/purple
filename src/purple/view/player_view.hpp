#pragma once

#include "view.hpp"
#include "canvas.hpp"
#include "resources.hpp"
#include <map>
#include <memory>
#include <unordered_map>

class PlayerView : public View {
public:
    PlayerView();

    void loadResources();

    void onActorSpawn(std::shared_ptr<Actor> actor) override;

    void update(double deltaSec) override;
    void render() override;

private:
    Canvas _canvas;
    Resources _resources;

    // It should be some kind of Scene here. For now, just use a vector of
    // drawable objects.
    // The Scene should manage drawable objects with positions itself. These
    // objects may form some kind of scene graph/qtree/rtree, whatever. Elements
    // of scene should have (weak?) connection with actors, and be easily found
    // by actor pointer/id, so that they can be quickly updated/removed when
    // a notification comes from the game core.
    std::map<WorldPoint, std::shared_ptr<sdl::Texture>> _drawables;
};