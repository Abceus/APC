#pragma once

#include "apc/coord.h"

#include "apc/specialization_check.h"

#include <type_traits>

namespace apc
{
    enum Orietation
    {
        Collinear,
        Clock,
        Clockwise
    };

    template<typename T>
    struct Line
    {
        Coord<T> start;
        Coord<T> end;

        Line<T> operator+ (const T& rhs);

        Line<T> operator- (const T& rhs);

        Line<T> operator* (const T& rhs);

        Line<T> operator/ (const T& rhs);

        Line<T> operator+ (const Line<T>& rhs);

        Line<T> operator- (const Line<T>& rhs);

        Line<T> operator* (const Line<T>& rhs);

        Line<T> operator/ (const Line<T>& rhs);

        static Line<T> scale(const Line<T>& origin, float factor);

        static Line<T> lengthen(const Line<T>& origin, T len);

        static bool insideSquade(const Line<T>& squadeBoardes, const Coord<T>& point);

        static Orietation linesOrientation(const Coord<T>& a, const Coord<T>& b, const Coord<T>& c);

        static bool isIntersected(const Line<T>& line1, const Line<T>& line2);

        T length() const;

        float angle() const;

        using type = T;
    };

    typedef Line<int> ILine;
    typedef Line<float> FLine;
    typedef Line<double> DLine;

    template<typename T1, typename T2, typename T3 = typename std::enable_if<is_specialization<T1, Line>::value, typename T1::type>::type>
    Line<T3> coord_cast(Coord<T2> value)
    {
        return Line<T3>{ { static_cast<T3>(value.start.x), static_cast<T3>(value.start.y) }, 
        { static_cast<T3>(value.end.x), static_cast<T3>(value.end.y) } };
    }
}