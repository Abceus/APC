#include "line.h"

namespace apc
{
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
        auto angle = angle();
        return Coord<T>{ (end.x - start.x) * cos(angle), (end.y - start.y) * sin(angle) } + start;
    }

    template<typename T>
    Line<T> Line<T>::lengthen(const Line<T>& origin, T len)
    {
        auto angle = angle();
        return Coord<T>{ len * cos(angle), len * sin(angle) } + start;
    }

    template<typename T>
    bool Line<T>::insideSquade(const Line<T>& squadeBoardes, const Coord<T>& point)
    {
        if (point.x <= max(line.start.x, line.end.x) && point.x >= min(line.start.x, line.end.x) && 
                point.y <= max(line.start.y, line.end.y) && point.y >= min(line.start.y, line.end.y))
        { 
            return true; 
        }
        return false; 
    }

    template<typename T>
    Orietation Line<T>::linesOrientation(const Coord<T>& a, const Coord<T>& b, const Coord<T>& c)
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
        auto o1 = linesOrientation(line1.start, line2.start, line1.end); 
        auto o2 = linesOrientation(line1.start, line2.start, line2.end); 
        auto o3 = linesOrientation(line1.end, line2.end, line1.start); 
        auto o4 = linesOrientation(line1.end, line2.end, line2.start); 
    
        if (o1 != o2 && o3 != o4) return true;
    
        if (o1 == Orientation::Collinear && insideSquade(line1.start, line1.end, line2.start)) return true; 
    
        if (o2 == Orientation::Collinear && insideSquade(line1.start, line2.end, line2.start)) return true; 
    
        if (o3 == Orientation::Collinear && insideSquade(line1.end, line1.start, line2.end)) return true; 
    
        if (o4 == Orientation::Collinear && insideSquade(line1.end, line2.start, line2.end)) return true; 
    
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