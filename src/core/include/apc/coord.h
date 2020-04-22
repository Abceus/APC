#pragma once

#include "apc/specialization_check.h"
#include "apc/math_utils.h"
#include "apc/matrix.h"

#include <type_traits>

namespace apc
{
    template<typename T>
    struct Coord
    {
        T x = T();
        T y = T();

        Coord<T> operator+ (const T& rhs) const;

        Coord<T> operator- (const T& rhs) const;

        Coord<T> operator* (const T& rhs) const;

        Coord<T> operator/ (const T& rhs) const;

        Coord<T> operator+ (const Coord<T>& rhs) const;

        Coord<T> operator- (const Coord<T>& rhs) const;

        Coord<T> operator* (const Coord<T>& rhs) const;

        Coord<T> operator/ (const Coord<T>& rhs) const;

        static T distance(const Coord<T>& first, const Coord<T>& second);

        static float angleBetween(const Coord<T>& first, const Coord<T>& second);

        static Coord<T> getTransformed(const Coord<T>& point, const Matrixf33& matrix);

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

    template<typename T>
    Coord<T> Coord<T>::operator+ (const T& rhs) const
    {
        Coord<T> res;
        res.x = x + rhs;
        res.y = y + rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator- (const T& rhs) const
    {
        Coord<T> res;
        res.x = x - rhs;
        res.y = y - rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator* (const T& rhs) const
    {
        Coord<T> res;
        res.x = x * rhs;
        res.y = y * rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator/ (const T& rhs) const
    {
        Coord<T> res;
        res.x = x / rhs;
        res.y = y / rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator+ (const Coord<T>& rhs) const
    {
        Coord<T> res;
        res.x = x + rhs.x;
        res.y = y + rhs.y;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator- (const Coord<T>& rhs) const
    {
        Coord<T> res;
        res.x = x - rhs.x;
        res.y = y - rhs.y;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator* (const Coord<T>& rhs) const
    {
        Coord<T> res;
        res.x = x * rhs.x;
        res.y = y * rhs.y;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator/ (const Coord<T>& rhs) const
    {
        Coord<T> res;
        res.x = x / rhs.x;
        res.y = y / rhs.y;
        return res;
    }

    template<typename T>
    T Coord<T>::distance(const Coord<T>& first, const Coord<T>& second)
    {
        return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
    }

    template<typename T>
    float Coord<T>::angleBetween(const Coord<T>& first, const Coord<T>& second)
    {
        float angle = degrees( static_cast<float>( atan2( second.y - first.y, second.x - first.x ) ) );
        return angle < 0.0f ? angle + 360.0f : angle;
    }

    template<typename T>
    Coord<T> Coord<T>::getTransformed(const Coord<T>& point, const Matrixf33& matrix)
    {
        Matrix<float, 3, 1> pointMatrix;
        pointMatrix[0][0] = point.x;
        pointMatrix[0][1] = point.y;
        pointMatrix[0][2] = static_cast<T>(1);

        pointMatrix = matrix * pointMatrix; 
        return Coord<T>{ pointMatrix[0][0], pointMatrix[0][1] };
    }
}