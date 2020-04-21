#include "core/coord.h"

#include <cmath>

namespace apc
{
    template<typename T>
    Coord<T> Coord<T>::operator+ (const T& rhs)
    {
        Coord<T> res;
        res.x = x + rhs;
        res.y = y + rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator- (const T& rhs)
    {
        Coord<T> res;
        res.x = x - rhs;
        res.y = y - rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator* (const T& rhs)
    {
        Coord<T> res;
        res.x = x * rhs;
        res.y = y * rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator/ (const T& rhs)
    {
        Coord<T> res;
        res.x = x / rhs;
        res.y = y / rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator+ (const Coord<T>& rhs)
    {
        Coord<T> res;
        res.x = x + rhs;
        res.y = y + rhs;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator- (const Coord<T>& rhs)
    {
        Coord<T> res;
        res.x = x - rhs.x;
        res.y = y - rhs.y;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator* (const Coord<T>& rhs)
    {
        Coord<T> res;
        res.x = x * rhs.x;
        res.y = y * rhs.y;
        return res;
    }

    template<typename T>
    Coord<T> Coord<T>::operator/ (const Coord<T>& rhs)
    {
        Coord<T> res;
        res.x = x / rhs.x;
        res.y = y / rhs.y;
        return res;
    }

    template<typename T>
    T Coord<T>::distance(const Coord<T>& first, const Coord<T>& second)
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    template<typename T>
    T Coord<T>::angleBetween(const Coord<T>& first, const Coord<T>& second)
    {
        T angle = degrees(atan2(second.y - first.y, second.x - first.x));
        return angle < 0 ? angle + 360 : angle;
    }
}