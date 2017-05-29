#pragma once

/**
* Below is a little clarification and motivation for the component architecture
* being used.
*
*  1. Each component has a type. Component types are defined in ComponentType
*     enumeration.
*
*  2. We use the following class hierarchy for components:
*
*     - Component
*       Base class of all components. Stores the component type used at
*       construction.
*
*     - ExactComponent<ComponentType>
*       Template for creating concrete component types. Stores component type
*       provided in template parameter statically, and passes it to Component
*       constructor; thus providing default constructor for its children.
*
*     - Any concrete concrete component class must have its own value in the
*       ComponentType enumeration, and derives from related specialization of
*       ExactComponent.
*
*     Note that no virtual functions are involved, so the inheritance is free
*     in terms of performance. In terms of memory, each component gets a
*     ComponentType value as its first member; and that is all.
*
*  3. To get concrete component class by ComponentType, we use a traits-like
*     struct ComponentOfHelper (usually via a helper alias, ComponentOf). Each
*     concreate component must "register" its type using specialization of
*     ComponentOfHelper.
*
* This clunky system provides one large benefit:
*
*     ---------------------------------------------------------------------
*     You do not have to include anything extra into your component's body.
*     ---------------------------------------------------------------------
*
* You don't have to declare a special member to bind your component to a
* ComponentType. The runtime binding is done in Component; the compile-time
* binding is performed in ExactComponent (one way) and ComponentOf (the other
* way).

* Basically, all housekeeping work is done outside of your component class's
* body. This allows us to use a macro to perform this work. COMPONENT is exactly
* that macro.
*/

#include "geometry.hpp"
#include <utility>

// NOTE:
// If this enumeration is getting giant, and annoying (because of everything
// depending on it, and the constant need to recompile everything), we may
// consider moving to GUIDs or something.

enum class ComponentType {
    Position,
};

struct Component {
    explicit Component(ComponentType type) : type(type) {}
    ComponentType type;
};

template <ComponentType CT>
struct ExactComponent : Component {
    ExactComponent() : Component(CT) {}
    static const ComponentType staticType = CT;
};

template <ComponentType CT>
struct ComponentOfHelper;

template <ComponentType CT>
using ComponentOf = typename ComponentOfHelper<CT>::Type;

#define COMPONENT(NAME, TYPE)                       \
    struct NAME;                                    \
    template <> struct ComponentOfHelper<TYPE> {    \
        using Type = NAME;                          \
    };                                              \
    struct NAME : ExactComponent<TYPE>

COMPONENT(PositionComponent, ComponentType::Position) {
    PositionComponent(WorldPoint position) : position(std::move(position)) {}
    WorldPoint position;
};

