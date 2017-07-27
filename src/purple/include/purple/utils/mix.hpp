#pragma once

#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <memory>
#include <map>

template <class Base>
class Mix {
public:
    template <class Exact>
    std::shared_ptr<Exact> get() const
    {
        static_assert(std::is_base_of<Base, Exact>::value,
            "Mix::get: type is not a subclass of Mix's base");

        auto i = _values.find(std::type_index(typeid(Exact)));
        if (i != _values.end()) {
            return std::static_pointer_cast<Exact, Base>(i->second);
        } else {
            return nullptr;
        }
    }

    template <class Exact>
    bool has() const
    {
        static_assert(std::is_base_of<Base, Exact>::value,
            "Mix::has: type is not a subclass of Mix's base");

        auto i = _values.find(std::type_index(typeid(Exact)));
        return i != _values.end();
    }

    template <class Exact>
    void put(std::shared_ptr<Exact> ptr)
    {
        static_assert(std::is_base_of<Base, Exact>::value,
            "Mix::put: type is not a subclass of Mix's base");

        _values[std::type_index(typeid(Exact))] = ptr;
        return ptr;
    }

    template <class Exact, class... Args>
    std::shared_ptr<Exact> emplace(Args&&... args)
    {
        static_assert(std::is_base_of<Base, Exact>::value,
            "Mix::emplace: type is not a subclass of Mix's base");

        auto ptr = std::make_shared<Exact>(std::forward<Args>(args)...);
        _values[std::type_index(typeid(Exact))] = ptr;
        return ptr;
    }

private:
    std::map<std::type_index, std::shared_ptr<Base>> _values;
};