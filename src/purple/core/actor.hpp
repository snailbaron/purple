#pragma once

#include "component.hpp"
#include <string>
#include <vector>
#include <memory>
#include <utility>

class Actor {
public:
    void addComponent(std::shared_ptr<Component> component);

    template <ComponentType CT, class... Args>
    void emplaceComponent(Args&&... args)
    {
        _components.push_back(std::shared_ptr<Component>(
            new ComponentOf<CT>(std::forward<Args>(args)...)));
    }

private:
    std::string _name;
    std::vector<std::shared_ptr<Component>> _components;
};