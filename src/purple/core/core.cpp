#include "core.hpp"
#include "tile_map.h"

void Core::attach(std::shared_ptr<View> view)
{
    _views.push_back(view);
}

void Core::update(double deltaSec)
{
    forActiveViews(
        [deltaSec](std::shared_ptr<View> view) {
            view->update(deltaSec);
        });
}

void Core::spawn(std::shared_ptr<Actor> actor)
{
    _actors.push_back(actor);
    notifyViews(&View::onActorSpawn, actor);
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
    camera->emplaceComponent<ComponentType::Camera>();
    camera->emplaceComponent<ComponentType::Position>(WorldPoint(10, 10));
    spawn(camera);

    auto tree = std::make_shared<Actor>();
    tree->name("tree");
    tree->emplaceComponent<ComponentType::Position>(WorldPoint(5, 15));
    tree->emplaceComponent<ComponentType::Graphics>("bitmaps/tree.png");
    spawn(tree);

    auto girl = std::make_shared<Actor>();
    girl->name("girl");
    girl->emplaceComponent<ComponentType::Position>(WorldPoint(9, 12));
    girl->emplaceComponent<ComponentType::Graphics>("animations/girl2.png");
    spawn(girl);
}