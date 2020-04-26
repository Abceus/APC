#pragma once

#include "apc/coord.h"

namespace apc
{
    class VertexBatcher;

    class IDrawable 
    {
    public:
        virtual void draw(VertexBatcher& batcher) = 0;
        virtual FCoord getHotspot() const = 0;
        virtual FCoord getSize() const = 0;
    };
}