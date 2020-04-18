#include "core/coord.h"

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
}