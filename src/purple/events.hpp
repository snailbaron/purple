#pragma once

#include "utils/variation.hpp"

enum class EventType {
    ActorSpawned,
};

using Event = Variation<EventType>;

template <EventType ET>
using EventOf = typename VariationOf<EventType, ET>;

#define EVENT(TYPE) \
    NEW_VARIATION(TYPE ## Event, EventType, EventType:: TYPE)

EVENT(ActorSpawned) {
    
};