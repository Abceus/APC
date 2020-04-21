#pragma once

#include "apc/coord.h"

namespace apc
{
    class IDrawable 
    {
    public:
        virtual void draw() = 0;
        virtual FCoord getHotspot() const = 0;
        virtual FCoord getSize() const = 0;
    };
}