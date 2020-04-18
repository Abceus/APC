#pragma once
#include <core/coord.h>

namespace apc
{
    class IScreenSensative
    {
    public:
        virtual void screenSizeChanged(const ICoord& newSize) = 0;
    };
}