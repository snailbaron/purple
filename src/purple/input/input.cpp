#include <purple/input/input.hpp>

#include <SDL.h>

#include <map>

namespace input {

namespace {

Button mouseButton(Uint8 button)
{
    std::map<Uint8, Button> mapping {
        { SDL_BUTTON_LEFT, Button::MouseLeft },
        { SDL_BUTTON_RIGHT, Button::MouseRight },
        { SDL_BUTTON_MIDDLE, Button::MouseMiddle },
    };

    return mapping[button];
}

} // namespace

void InputManager::processInput()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            _eventQueue.push(QuitEvent{});
        } else if (evt.type == SDL_MOUSEBUTTONDOWN) {
            _eventQueue.push(ButtonEvent{
                mouseButton(evt.button.button),
                ButtonEvent::Action::Press,
                evt.button.x,
                evt.button.y});
        } else if (evt.type == SDL_MOUSEBUTTONUP) {
            _eventQueue.push(ButtonEvent{
                mouseButton(evt.button.button),
                ButtonEvent::Action::Release,
                evt.button.x,
                evt.button.y});
        } else if (evt.type == SDL_MOUSEMOTION) {
            _eventQueue.push(PointerMotionEvent{
                evt.motion.x, evt.motion.y, evt.motion.xrel, evt.motion.yrel});
        }
    }

    _eventQueue.send();
}

} // namespace input