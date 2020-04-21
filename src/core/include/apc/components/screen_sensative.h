#pragma once
#include <apc/coord.h>

namespace apc
{
    class IScreenSensative
    {
    public:
        virtual void screenSizeChanged(const ICoord& newSize) = 0;
    };
}