#pragma once

#include <typeindex>
#include <map>
#include <vector>
#include <any>
#include <set>
#include <tuple>
#include <functional>

class EventQueue;

class AnyListener {
public:
    virtual void dispatch(const EventQueue& queue) = 0;
};

template <class Event>
class Listener : public AnyListener {
public:
    virtual void listen(const Event& event) = 0;

    void dispatch(const EventQueue& queue) override
    {
        queue.request(this);
    }
};

class EventQueue {
public:
    template <class Event>
    void subscribe(Listener<Event>* listener)
    {
        auto eventTypeIndex = std::type_index(typeid(Event));

        auto it = _listeners.find(eventTypeIndex);
        if (it == _listeners.end()) {
            std::tie(it, std::ignore) =
                _listeners.emplace(eventTypeIndex, std::set<AnyListener*>{});
        }
        it->second.insert(listener);
    }

    template <class Event>
    void unsubscribe(Listener<Event>* listener)
    {
        auto eventTypeIndex = std::type_index(typeid(Event));
        auto eventListenersPairIter = _listeners.find(eventTypeIndex);
        if (eventListenersPairIter != _listeners.end()) {
            std::set<AnyListener*>& listeners = eventListenersPairIter->second;
            auto listenerIter = listeners.find(listener);
            if (listenerIter != listeners.end()) {
                listeners.remove(listenerIter);
            }
        }
    }

    template <class Event>
    void push(Event event)
    {
        _events[std::type_index(typeid(Event))].push_back(std::move(event));
    }

    void send()
    {
        for (const auto& eventListenerPair : _listeners) {
            for (AnyListener* listener : eventListenerPair.second) {
                listener->dispatch(*this);
            }
        }
        _events.clear();
    }

    template <class Event>
    void request(Listener<Event>* listener) const
    {
        auto eventTypeIndex = std::type_index(typeid(Event));
        auto eventsIter = _events.find(eventTypeIndex);
        if (eventsIter == _events.end()) {
            return;
        }

        for (const std::any& rawEvent : eventsIter->second) {
            Event event = std::any_cast<Event>(rawEvent);
            listener->listen(event);
        }
    }

private:
    std::map<std::type_index, std::set<AnyListener*>> _listeners;
    std::map<std::type_index, std::vector<std::any>> _events;
};