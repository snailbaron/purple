#include "component.hpp"
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

    double maxAcc = movement->maxAcceleration;
    movement->acceleration.x = x * maxAcc;
    movement->acceleration.y = y * maxAcc;
}