#include "core.hpp"

void Core::attach(std::shared_ptr<View> view)
{
    _views.push_back(view);
}

void Core::update(double deltaSec)
{
    forActiveViews(
        [deltaSec](std::shared_ptr<View> view) {
            view->update(deltaSec);
        });
}

void Core::spawn(std::shared_ptr<Actor> actor)
{
    _actors.push_back(actor);
    forActiveViews(
        [actor](std::shared_ptr<View> view) {
            view->onActorSpawn(actor);
        }
    );
}

void Core::forActiveViews(std::function<void(std::shared_ptr<View>)> action)
{
    for (auto i = _views.begin(); i != _views.end(); ) {
        auto ptr = i->lock();
        if (ptr) {
            action(ptr);
            i++;
        } else {
            i = _views.erase(i);
        }
    }
}