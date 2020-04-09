#pragma once

namespace APC
{
    struct Coord
    {
        int x = 0;
        int y = 0;
        friend Coord operator+(Coord lhs, const Coord& rhs) 
        {
            lhs.x += rhs.x;
            lhs.y += rhs.y;
            return lhs; 
        }
    };

    struct FCoord
    {
        float x = 0.0f;
        float y = 0.0f;
    };
}