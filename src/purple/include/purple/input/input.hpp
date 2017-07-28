#pragma once

#include <purple/events.hpp>

namespace input {

enum class Button {
    // Mouse buttons
    MouseLeft,
    MouseMiddle,
    MouseRight,
};

struct ButtonEvent {
    enum class Action {
        Press,
        Release,
    };

    Button button;
    Action action;
    int x;
    int y;
};

struct PointerMotionEvent {
    int x;
    int y;
    int dx;
    int dy;
};

struct QuitEvent {};

class InputManager {
public:
    void processInput();

    template <class Event>
    void subscribe(Listener<Event>* listener)
    {
        _eventQueue.subscribe<Event>(listener);
    }

private:
    EventQueue _eventQueue;
};

} // namespace input