#pragma once

#include <utils/variation.hpp>

#include "geometry.hpp"
#include <utility>
#include <string>

enum class ComponentType {
    Position,
    Graphics,
};

using Component = Variation<ComponentType>;

template <ComponentType CT>
using ComponentOf = typename VariationOf<ComponentType, CT>;

#define NEW_COMPONENT(NAME, TYPE) NEW_VARIATION(NAME, ComponentType, TYPE)

NEW_COMPONENT(PositionComponent, ComponentType::Position) {
    PositionComponent(WorldPoint position) : position(std::move(position)) {}
    WorldPoint position;
};

NEW_COMPONENT(GraphicsComponent, ComponentType::Graphics) {
    GraphicsComponent(std::string graphics) : graphics(std::move(graphics)) {}
    std::string graphics;
};