#pragma once

#include <utils/variation.hpp>

#include "geometry.hpp"
#include <utility>
#include <string>

enum class ComponentType {
    Position,
    Graphics,
    Camera,
    TileMap,
};

using Component = Variation<ComponentType>;

template <ComponentType CT>
using ComponentOf = typename VariationOf<ComponentType, CT>;

#define NEW_COMPONENT(TYPE) \
    NEW_VARIATION(TYPE ## Component, ComponentType, ComponentType:: TYPE)

NEW_COMPONENT(Position) {
    PositionComponent(WorldPoint position) : position(std::move(position)) {}
    WorldPoint position;
};

NEW_COMPONENT(Graphics) {
    GraphicsComponent(std::string graphics) : graphics(std::move(graphics)) {}
    std::string graphics;
};

NEW_COMPONENT(Camera) {
};

NEW_COMPONENT(TileMap) {
    
};