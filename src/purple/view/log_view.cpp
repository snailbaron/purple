#include "log_view.hpp"
#include <iostream>

void LogView::onActorSpawn(std::shared_ptr<Actor> actor)
{
    std::cout << "Actor spawned: " << actor->name() << std::endl;
}

void LogView::onTilesLoaded(const TileMap& tileMap)
{
    std::cout << "Tiles loaded" << std::endl;
}