#pragma once

#include "apc/coord.h"

#include "apc/specialization_check.h"

#include <type_traits>
#include <algorithm>

namespace apc
{
    enum Orientation
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

        static Orientation linesOrientation(const Coord<T>& a, const Coord<T>& b, const Coord<T>& c);

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

    template<typename T>
    Line<T> Line<T>::operator+ (const T& rhs)
    {
        Line<T> res;
        res.start = start + rhs;
        res.end = end + rhs;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator- (const T& rhs)
    {
        Line<T> res;
        res.start = start - rhs;
        res.end = end - rhs;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator* (const T& rhs)
    {
        Line<T> res;
        res.start = start * rhs;
        res.end = end * rhs;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator/ (const T& rhs)
    {
        Line<T> res;
        res.start = start / rhs;
        res.end = end / rhs;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator+ (const Line<T>& rhs)
    {
        Line<T> res;
        res.start = start + rhs;
        res.end = end + rhs;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator- (const Line<T>& rhs)
    {
        Line<T> res;
        res.start = start - rhs.start;
        res.end = end - rhs.end;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator* (const Line<T>& rhs)
    {
        Line<T> res;
        res.start = start * rhs.start;
        res.end = end * rhs.end;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::operator/ (const Line<T>& rhs)
    {
        Line<T> res;
        res.start = start / rhs.start;
        res.end = end / rhs.end;
        return res;
    }

    template<typename T>
    Line<T> Line<T>::scale(const Line<T>& origin, float factor)
    {
        auto angle = origin.angle();
        return Coord<T>{ (origin.end.x - origin.start.x) * cos(angle), (origin.end.y - origin.start.y) * sin(angle) } + origin.start;
    }

    template<typename T>
    Line<T> Line<T>::lengthen(const Line<T>& origin, T len)
    {
        auto angle = origin.angle();
        return Coord<T>{ len * cos(angle), len * sin(angle) } + origin.start;
    }

    template<typename T>
    bool Line<T>::insideSquade(const Line<T>& squadeBoardes, const Coord<T>& point)
    {
        if (point.x <= std::max(squadeBoardes.start.x, squadeBoardes.end.x) && point.x >= std::min(squadeBoardes.start.x, squadeBoardes.end.x) && 
                point.y <= std::max(squadeBoardes.start.y, squadeBoardes.end.y) && point.y >= std::min(squadeBoardes.start.y, squadeBoardes.end.y))
        { 
            return true; 
        }
        return false; 
    }

    template<typename T>
    Orientation Line<T>::linesOrientation(const Coord<T>& a, const Coord<T>& b, const Coord<T>& c)
    {
        int orientation = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y); 
    
        if(orientation == 0) 
        {
            return Orientation::Collinear;
        } 
        else if(orientation > 0)
        {
            return Orientation::Clock;
        }

        return Orientation::Clockwise;
    }

    template<typename T>
    bool Line<T>::isIntersected(const Line<T>& line1, const Line<T>& line2)
    {
        auto o1 = linesOrientation(line1.start, line1.end, line2.start); 
        auto o2 = linesOrientation(line1.start, line1.end, line2.end); 
        auto o3 = linesOrientation(line2.start, line2.end, line1.start); 
        auto o4 = linesOrientation(line2.start, line2.end, line1.end); 
        
        if (o1 != o2 && o3 != o4) return true;
    
        if (o1 == Orientation::Collinear && insideSquade(line1, line2.start)) return true; 
    
        if (o2 == Orientation::Collinear && insideSquade(line1, line2.end)) return true; 
    
        if (o3 == Orientation::Collinear && insideSquade(line2, line1.start)) return true; 
    
        if (o4 == Orientation::Collinear && insideSquade(line2, line1.end)) return true; 
    
        return false; 
    }

    template<typename T>
    T Line<T>::length() const
    {
        return Coord<T>::distance(start, end);
    }
        
    template<typename T>
    float Line<T>::angle() const
    {
        return Coord<T>::angleBetween(start, end);
    }
}