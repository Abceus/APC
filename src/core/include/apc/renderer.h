#pragma once

#include <memory>
#include "apc/scene.h"

namespace apc
{
    class VertexBatcher;
    
    class IRenderer
    {
    public:
        virtual void init() = 0;
        virtual void screenChange(int w, int h) = 0;
        virtual void draw(const VertexBatcher& batcher) = 0;
        virtual void destroy() = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual FCoord getScaledScreenSize() const = 0;
        virtual ~IRenderer() = default;
    };
}