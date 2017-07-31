#pragma once

#include <purple/events.hpp>

namespace input {

enum class MenuButton {
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

    MenuButton button;
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
        _outEvents.subscribe<Event>(listener);
    }

private:
    EventQueue _outEvents;
};

} // namespace input