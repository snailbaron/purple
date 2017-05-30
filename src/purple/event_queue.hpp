#pragma once

#include "events.hpp"
#include <functional>
#include <memory>
#include <map>
#include <vector>
#include <queue>

template <EventType ET>
using EventHandler = std::function<void(std::shared_ptr<EventOf<ET>>)>;

class EventHandlerHolder {
public:
    virtual void invoke(std::shared_ptr<Event> evt) const = 0;
};

template <EventType ET>
class ExactEventHandlerHolder : EventHandlerHolder {
public:
    ExactEventHandlerHolder(EventHandler<ET> handler)
        : _handler(handler) {}

    void invoke(std::shared_ptr<Event> evt) const override
    {
        _handler(std::static_pointer_cast<EventOf<ET>, Event>(evt));
    }

private:
    EventHandler<ET> _handler;
};

class EventQueue {
public:
    template <EventType ET>
    void subscribe(EventHandler<ET> handler)
    {
        _handlers[ET].push_back(std::shared_ptr<EventHandlerHolder>(
            new ExactEventHandlerHolder(handler)));
    }

    void send()
    {
        while (!_events.empty()) {
            auto evt = _events.front();
            _events.pop();
            for (const auto& handler : _handlers[evt->type]) {
                handler.invoke(evt);
            }
        }
    }

    template <EventType ET>
    void push(std::shared_ptr<EventOf<ET>> evt)
    {
        _events.push(std::static_pointer_cast<Event, EventOf<ET>>(evt));
    }

private:
    std::queue<std::shared_ptr<Event>> _events;
    std::map<EventType, std::vector<EventHandlerHolder>> _handlers;
};