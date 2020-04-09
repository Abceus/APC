#pragma once

#include <memory>

#include "core/drawable.h"

namespace APC
{
    class IRenderer
    {
    public:
        virtual void init(int w, int h) = 0;
        virtual void draw() = 0;
        virtual void destroy() = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual ~IRenderer() = default;
    };
}