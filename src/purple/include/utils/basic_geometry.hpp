#pragma once

/**
 * Universal 2-dimensional geometry. May be used for tracking screen coordinates
 * (in pixels, centimeters, percents of whole screen, etc) or world coordinates
 * (in-game meters, etc).
 */

#include <type_traits>
#include <tuple>

template <class T>
struct Vector {
    static_assert(std::is_arithmetic<T>::value,
        "Vector: can only wrap arithmetic types");

    Vector() : x(0), y(0) {}
    Vector(T x, T y) : x(x), y(y) {}

    //
    // Binary arithmetic operators
    //

    Vector& operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector& operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Multiplier must be convertible to T to get vector of the same type
    Vector& operator*=(const T& mul)
    {
        x *= mul;
        y *= mul;
        return *this;
    }

    // Divisor must be convertible to T to get vector of the same type
    Vector& operator/=(const T& div)
    {
        x /= div;
        y /= div;
        return *this;
    }

    T x;
    T y;
};

template <class T>
Vector<T> operator+(Vector<T> left, const Vector<T>& right)
{
    left += right;
    return left;
}

template <class T>
Vector<T> operator-(Vector<T> left, const Vector<T>& right)
{
    left -= right;
    return left;
}

// Universal multiplication and division: accept any scalar value, return a
// vector of appropriate type.

template <class T, class Scalar>
Vector<decltype(std::declval<T>() * std::declval<Scalar>())>
operator*(const Vector<T>& vec, Scalar mul)
{
    return {vec.x * mul, vec.y * mul};
}

template <class T, class Scalar>
Vector<decltype(std::declval<T>() * std::declval<Scalar>())>
operator*(Scalar mul, const Vector<T>& vec)
{
    return vec * mul;
}

template <class T, class Scalar>
Vector<decltype(std::declval<T>() / std::declval<Scalar>())>
operator/(const Vector<T>& vec, Scalar div)
{
    return {vec.x / div, vec.y / div};
}

// Special case multiplication and division: scalar is of the same type as
// vector components; can reuse the vector.

template <class T>
Vector<T> operator*(Vector<T> vec, T mul)
{
    vec *= mul;
    return vec;
}

template <class T>
Vector<T> operator*(T mul, Vector<T> vec)
{
    vec *= mul;
    return vec;
}

template <class T>
Vector<T> operator/(Vector<T> vec, T div)
{
    vec /= div;
    return vec;
}

//
// Relational operators.
//
// Comparison operators (<, <=, >, >=) are defined in C++ terms, not in usual
// mathematical terms. This is to avoid nasty surprises when using std::set,
// std::map, etc. For mathematical comparison, related member functions are
// used.
//

template <class T>
bool operator==(const Vector<T>& left, const Vector<T>& right)
{
    return std::tie(left.x, left.y) == std::tie(right.x, right.y);
}

template <class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right)
{
    return !(left == right);
}

template <class T>
bool operator<(const Vector<T>& left, const Vector<T>& right)
{
    return std::tie(left.x, left.y) < std::tie(right.x, right.y);
}

template <class T>
bool operator<=(const Vector<T>& left, const Vector<T>& right)
{
    return left < right || left == right;
}

template <class T>
bool operator>(const Vector<T>& left, const Vector<T>& right)
{
    return right < left;
}

template <class T>
bool operator>=(const Vector<T>& left, const Vector<T>& right)
{
    return right <= left;
}

//
// static_cast analog for vectors
// TODO: Some zero-copy thingy for trivial T1==T2 case?
//

template <class T1, class T2>
Vector<T1> staticVectorCast(const Vector<T2>& source)
{
    return {
        static_cast<T1>(source.x),
        static_cast<T1>(source.y)
    };
}

