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
        friend FCoord operator+(FCoord lhs, const FCoord& rhs) 
        {
            lhs.x += rhs.x;
            lhs.y += rhs.y;
            return lhs; 
        }
    };

    struct Color
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;

        friend Color operator+(Color lhs, const Color& rhs) 
        {
            lhs.r += rhs.r;
            lhs.g += rhs.g;
            lhs.b += rhs.b;
            lhs.a += rhs.a;
            return lhs; 
        }

        friend Color operator*(Color lhs, const Color& rhs) 
        {
            lhs.r *= rhs.r;
            lhs.g *= rhs.g;
            lhs.b *= rhs.b;
            lhs.a *= rhs.a;
            return lhs; 
        }
    };
}