#pragma once

#include "geometry.hpp"
#include <utility>
#include <string>
#include <memory>

class Actor;

struct Component {
    std::weak_ptr<Actor> actorPtr;
};

struct PositionComponent : Component {
    PositionComponent(WorldPoint position) : position(std::move(position)) {}
    WorldPoint position;
};

struct GraphicsComponent : Component {
    GraphicsComponent(std::string graphics) : graphics(std::move(graphics)) {}
    std::string graphics;
};

struct CameraComponent : Component {
    CameraComponent(std::weak_ptr<PositionComponent> followPosition)
        : followPosition(followPosition) {}
    std::weak_ptr<PositionComponent> followPosition;
};

struct ControllerComponent : Component {
    void setInput(double x, double y);
};

struct MovementComponent : Component {
    MovementComponent(double maxSpeed, double acceleration, double friction)
        : maxSpeed(maxSpeed)
        , friction(friction)
        , maxAcceleration(acceleration + friction)
    { }

    WorldVector velocity;
    WorldVector acceleration;
    double maxSpeed;
    double friction;
    double maxAcceleration;
};