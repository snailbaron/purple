#pragma once

#include <utility>
#include <stdexcept>
#include <type_traits>
#include <string>
#include <memory>

template <class T>
class HeapHolder {
public:
    template <class... Args>
    void emplace(Args&&... args)
    {
        _ptr = std::make_unique<T>(std::forward<Args>(args)...);
    }

    void reset()
    {
        _ptr.reset();
    }

    explicit operator bool() const noexcept
    {
        return !!_ptr;
    }

    T& value() { return *_ptr; }
    const T& value() const { return *_ptr; }

private:
    std::unique_ptr<T> _ptr;
};

template <class T>
struct SingletonTraits {
    using Holder = HeapHolder<T>;
};

/**
 * Singleton with explicit initialization and destruction
 */
template <class T>
class Singleton {
    using Holder = typename SingletonTraits<T>::Holder;

public:
    template <class... Args>
    static void initialize(Args&&... args)
    {
        if (_holder) {
            throw std::runtime_error(typeName() + ": already initialized");
        }
        _holder.emplace(std::forward<Args>(args)...);
    }

    static void destroy()
    {
        if (!_holder) {
            throw std::runtime_error(
                typeName() + ": not initialized, but destroy() called ");
        }
        _holder.reset();
    }

    template <class U = T>
    static std::enable_if_t<std::is_default_constructible<U>::value, T&>
    instance()
    {
        if (!_holder) {
            initialize();
        }
        return _holder.value();            
    }

    template <class U = T>
    static std::enable_if_t<!std::is_default_constructible<U>::value, T&>
    instance()
    {
        if (!_holder) {
            throw std::runtime_error(
                typeName() + ": instance() is called, but the type is not" +
                " initialized, and is not default constructible");
        }
        return _holder.value();
    }

private:
    static std::string typeName()
    {
        return std::string("Singleton<") + typeid(T).name() + ">";
    }

    static Holder _holder;
};

template <class T>
typename Singleton<T>::Holder Singleton<T>::_holder;

