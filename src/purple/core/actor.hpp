#pragma once

#include "component.hpp"
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include <set>

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
        auto i = _components.find(CT);
        if (i != _components.end()) {
            return std::static_pointer_cast<ComponentOf<CT>, Component>(
                i->second);
        } else {
            return nullptr;
        }
    }

    std::set<ComponentType> componentTypes()
    {
        std::set<ComponentType> result;
        for (const auto& pair : _components) {
            result.insert(pair.first);
        }
        return result;
    }

private:
    std::string _name;
    std::map<ComponentType, std::shared_ptr<Component>> _components;
};