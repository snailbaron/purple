#pragma once

#include "canvas.hpp"
#include "visual.hpp"

#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include <initializer_list>

class Widget {
public:
    virtual ~Widget() {}

    //virtual void listen(InputEvent& event) = 0;
    virtual void update(double deltaSec) = 0;
    virtual void render(Canvas& renderer) = 0;
};

class WidgetPanel {
public:
    void contents(std::initializer_list<std::unique_ptr<Widget>> widgets);

private:
    std::vector<std::unique_ptr<Widget>> _widgets;
};

/**
 * Button with text used in menus
 */
class MenuButton : public Widget {
public:
    MenuButton(
        ScreenPosition position,
        const std::string& text,
        std::function<void()> action);

    void update(double deltaSec) override {}
    void render(Canvas& canvas) override {}

    MenuButton& position(ScreenPosition position)
    {
        _position = std::move(position);
    }

    template <class T>
    MenuButton& visual()
    {
        _visual = std::make_unique<T>();
    }

private:
    ScreenPosition _position;
    std::unique_ptr<Visual> _visual;
    std::function<void()> _action;
};