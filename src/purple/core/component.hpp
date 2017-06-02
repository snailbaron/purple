#pragma once

#include <utils/variation.hpp>

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
};

struct ControllerComponent : Component {
    void setInput(double x, double y);
};

struct MovementComponent : Component {
    MovementComponent(double maxSpeed, double maxAcceleration)
        : maxSpeed(maxSpeed), maxAcceleration(maxAcceleration) {}

    WorldVector speed;
    WorldVector acceleration;
    double maxAcceleration;
    double maxSpeed;
};