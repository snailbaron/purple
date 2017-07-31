#include <purple/input/input.hpp>

#include <SDL.h>

#include <map>

namespace input {

namespace {

MenuButton mouseButton(Uint8 button)
{
    std::map<Uint8, MenuButton> mapping {
        { SDL_BUTTON_LEFT, MenuButton::MouseLeft },
        { SDL_BUTTON_RIGHT, MenuButton::MouseRight },
        { SDL_BUTTON_MIDDLE, MenuButton::MouseMiddle },
    };

    return mapping[button];
}

} // namespace

void InputManager::processInput()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            _outEvents.push(QuitEvent{});
        } else if (evt.type == SDL_MOUSEBUTTONDOWN) {
            _outEvents.push(ButtonEvent{
                mouseButton(evt.button.button),
                ButtonEvent::Action::Press,
                evt.button.x,
                evt.button.y});
        } else if (evt.type == SDL_MOUSEBUTTONUP) {
            _outEvents.push(ButtonEvent{
                mouseButton(evt.button.button),
                ButtonEvent::Action::Release,
                evt.button.x,
                evt.button.y});
        } else if (evt.type == SDL_MOUSEMOTION) {
            _outEvents.push(PointerMotionEvent{
                evt.motion.x, evt.motion.y, evt.motion.xrel, evt.motion.yrel});
        }
    }

    _outEvents.send();
}

} // namespace input