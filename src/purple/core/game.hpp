#pragma once

#include "../view/view.hpp"
#include "actor.hpp"
#include <purple/events.hpp>
#include <vector>
#include <memory>
#include <functional>
#include <utility>

struct GameStartedEvent {};

struct NewGameRequest {};

class Game
    : public Listener<NewGameRequest> {
public:
    void attach(View* view);
    void update(double deltaSec);
    void spawn(std::shared_ptr<Actor> actor);

    void start();

    template <class Request>
    void request(const Request& request)
    {
        _requests.push(request);
    }

private:
    // Imitates loading a level. For development purposes only.
    void loadTestLevel();

    void listen(const NewGameRequest&) override;

    void forActiveViews(std::function<void(std::shared_ptr<View>)> action);

    template <class ViewFunction, class... ArgTypes>
    void notifyViews(const ViewFunction& function, ArgTypes&&... args)
    {
        forActiveViews(
            [&](std::shared_ptr<View> view) {
                (view.get()->*function)(std::forward<ArgTypes>(args)...);
            });
    }

    std::vector<View*> _views;
    std::vector<std::shared_ptr<Actor>> _actors;

    EventQueue _outEvents;
    EventQueue _requests;
};