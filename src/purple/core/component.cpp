#include <purple/core/component.hpp>
#include "actor.hpp"

void ControllerComponent::setInput(double x, double y)
{
    auto actor = actorPtr.lock();
    if (!actor) {
        return;
    }

    auto movement = actor->get<MovementComponent>();
    if (!movement) {
        return;
    }

    movement->acceleration = WorldVector(x, y) * movement->maxAcceleration;
}