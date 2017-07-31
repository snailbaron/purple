#include "widget.hpp"

void WidgetPanel::contents(
    std::initializer_list<std::unique_ptr<Widget>> widgets)
{
    _widgets.clear();
    for (auto ptr : widgets) {
        _widgets.push_back(ptr);
    }
}

//
// MenuButton
//

MenuButton::MenuButton(
        ScreenPosition position,
        const std::string& text,
        std::function<void()> action)
    : _position(std::move(position))

