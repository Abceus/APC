#pragma once
#include <core/utility.h>

namespace APC
{
    class IScreenSensative
    {
    public:
        virtual void screenSizeChanged(const Coord& newSize) = 0;
    };
}