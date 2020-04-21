#pragma once

#include "core/specialization_check.h"

#include <type_traits>

namespace apc
{
    template<typename T>
    struct Coord
    {
        T x = T();
        T y = T();

        Coord<T> operator+ (const T& rhs);

        Coord<T> operator- (const T& rhs);

        Coord<T> operator* (const T& rhs);

        Coord<T> operator/ (const T& rhs);

        Coord<T> operator+ (const Coord<T>& rhs);

        Coord<T> operator- (const Coord<T>& rhs);

        Coord<T> operator* (const Coord<T>& rhs);

        Coord<T> operator/ (const Coord<T>& rhs);

        static T distance(const Coord<T>& first, const Coord<T>& second);

        static T angleBetween(const Coord<T>& first, const Coord<T>& second);

        using type = T;
    };

    typedef Coord<int> ICoord;
    typedef Coord<float> FCoord;
    typedef Coord<double> DCoord;

    template<typename T1, typename T2, typename T3 = typename std::enable_if<is_specialization<T1, Coord>::value, typename T1::type>::type>
    Coord<T3> coord_cast(Coord<T2> value)
    {
        return Coord<T3>{ static_cast<T3>(value.x), static_cast<T3>(value.y) };
    }
}