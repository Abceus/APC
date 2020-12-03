#pragma once

#include "apc/coord.h"

namespace apc
{
    class VertexBatcher;

    class IDrawable 
    {
    public:
        virtual void init() = 0;
        virtual void deinit() = 0;
        virtual void draw(VertexBatcher& batcher) = 0;
        virtual FCoord getHotspot() const = 0;
        virtual FCoord getSize() const = 0;
    };
}