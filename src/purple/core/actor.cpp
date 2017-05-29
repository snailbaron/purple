#include "actor.hpp"

void Actor::addComponent(std::shared_ptr<Component> component)
{
    _components.push_back(component);
}