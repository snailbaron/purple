#pragma once

#include "component.hpp"
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <map>

class Actor {
public:
    const std::string& name() const { return _name; }
    Actor& name(std::string name) { _name = std::move(name); return *this; }

    void addComponent(std::shared_ptr<Component> component);

    template <ComponentType CT, class... Args>
    void emplaceComponent(Args&&... args)
    {
        _components[CT] = std::shared_ptr<Component>(
            new ComponentOf<CT>(std::forward<Args>(args)...));
    }

    bool hasComponent(ComponentType type)
    {
        return _components.find(type) != _components.end();
    }

    template <ComponentType CT>
    std::shared_ptr<ComponentOf<CT>> getComponent()
    {
        return std::static_pointer_cast<ComponentOf<CT>, Component>(
            _components[CT]);
    }

private:
    std::string _name;
    std::map<ComponentType, std::shared_ptr<Component>> _components;
};