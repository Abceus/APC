#include "color.h"

namespace apc
{
    Color Color::operator+(const Color& rhs) 
    {
        Color res;
        res.r = r + rhs.r;
        res.g = g + rhs.g;
        res.b = b + rhs.b;
        res.a = a + rhs.a;
        return res; 
    }

    Color Color::operator*(const Color& rhs) 
    {
        Color res;
        res.r = r * rhs.r;
        res.g = g * rhs.g;
        res.b = b * rhs.b;
        res.a = a * rhs.a;
        return res; 
    }
}