#pragma once

#include "../view/view.hpp"
#include "actor.hpp"
#include <vector>
#include <memory>
#include <functional>
#include <utility>

class Core {
public:
    void attach(std::shared_ptr<View> view);
    void update(double deltaSec);
    void spawn(std::shared_ptr<Actor> actor);

    // Imitates loading a level. For development purposes only.
    void loadTestLevel();

private:
    void forActiveViews(std::function<void(std::shared_ptr<View>)> action);

    template <class ViewFunction, class... ArgTypes>
    void notifyViews(const ViewFunction& function, ArgTypes&&... args)
    {
        forActiveViews(
            [&](std::shared_ptr<View> view) {
                (view.get()->*function)(std::forward<ArgTypes>(args)...);
            });
    }

    std::vector<std::weak_ptr<View>> _views;
    std::vector<std::shared_ptr<Actor>> _actors;
};