#pragma once

#include <utils/variation.hpp>

#include "geometry.hpp"
#include <utility>
#include <string>

struct Component {};

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