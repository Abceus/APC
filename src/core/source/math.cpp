#include "math.h"

namespace apc
{
    float degrees(float rad)
    {
        return rad * 180.0f / PI;
    }

    float radians(float deg)
    {
        return deg * PI / 180.0f;
    }
}