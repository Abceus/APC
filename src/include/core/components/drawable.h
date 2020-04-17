#pragma once

#include "core/utility.h"

namespace APC
{
    class IDrawable 
    {
    public:
        virtual void draw() = 0;
        virtual FCoord getHotspot() const = 0;
        virtual FCoord getSize() const = 0;
    };
}