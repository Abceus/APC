#pragma once

namespace apc
{
    struct Color
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;

        Color operator+(const Color& rhs);

        Color operator*(const Color& rhs);
    };
}