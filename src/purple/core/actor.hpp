#pragma once

#include "component.hpp"
#include <utils/mix.hpp>
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

    template <class ExactComponent, class... ArgTypes>
    void emplace(ArgTypes&&... args)
    {
        _components.emplace<ExactComponent>(std::forward<ArgTypes>(args)...);
    }

    template <class ExactComponent>
    bool has()
    {
        return _components.has<ExactComponent>();
    }

    template <class ExactComponent>
    std::shared_ptr<ExactComponent> get()
    {
        return _components.get<ExactComponent>();
    }

private:
    std::string _name;
    Mix<Component> _components;
};