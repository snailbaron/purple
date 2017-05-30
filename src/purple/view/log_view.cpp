#include "log_view.hpp"
#include <iostream>

void LogView::onActorSpawn(std::shared_ptr<Actor> actor)
{
    std::cout << "Actor spawned: " << actor->name() << std::endl;
}