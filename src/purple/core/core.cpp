#include "core.hpp"
#include "tile_map.h"
#include "component.hpp"
#include <iostream>

void Core::attach(std::shared_ptr<View> view)
{
    _views.push_back(view);
}

void Core::update(double deltaSec)
{
    // Process movement
    for (auto actor : _actors) {
        auto movement = actor->get<MovementComponent>();
        if (movement) {
            std::cerr << movement->speed.x << ", " << movement->speed.y << std::endl;
            movement->speed += movement->acceleration;
            movement->speed.shorten(movement->maxSpeed);

            auto position = actor->get<PositionComponent>();
            if (position) {
                position->position += movement->speed;
            }
        }
    }

    forActiveViews(
        [deltaSec](std::shared_ptr<View> view) {
            view->update(deltaSec);
        });
}

void Core::spawn(std::shared_ptr<Actor> actor)
{
    _actors.push_back(actor);
    notifyViews(&View::onActorSpawn, actor);

    auto controller = actor->get<ControllerComponent>();
    if (controller) {
        notifyViews(&View::onControllerSpawn, controller);
    }
}

void Core::forActiveViews(std::function<void(std::shared_ptr<View>)> action)
{
    for (auto i = _views.begin(); i != _views.end(); ) {
        auto ptr = i->lock();
        if (ptr) {
            action(ptr);
            i++;
        } else {
            i = _views.erase(i);
        }
    }
}

void Core::loadTestLevel()
{
    TileSet tileSet;
    tileSet.fill({
        {"bitmaps/grass.png"},
        {"bitmaps/road.png"}
    });

    TileMap tileMap(tileSet);
    tileMap.fill(10, 10, {
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    });

    notifyViews(&View::onTilesLoaded, tileMap);

    auto camera = std::make_shared<Actor>();
    camera->name("camera");
    camera->emplace<CameraComponent>();
    camera->emplace<PositionComponent>(WorldPoint(10, 10));
    spawn(camera);

    auto tree = std::make_shared<Actor>();
    tree->name("tree");
    tree->emplace<PositionComponent>(WorldPoint(5, 15));
    tree->emplace<GraphicsComponent>("bitmaps/tree.png");
    spawn(tree);

    auto girl = std::make_shared<Actor>();
    girl->name("girl");
    girl->emplace<PositionComponent>(WorldPoint(9, 12));
    girl->emplace<GraphicsComponent>("animations/girl2.png");
    girl->emplace<MovementComponent>(10.0, 5.0);
    girl->emplace<ControllerComponent>();
    spawn(girl);
}