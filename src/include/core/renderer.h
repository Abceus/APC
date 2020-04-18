#pragma once

#include <memory>
#include "core/scene.h"

namespace apc
{
    class IRenderer
    {
    public:
        virtual void init() = 0;
        virtual void screenChange(int w, int h) = 0;
        virtual void draw(std::shared_ptr<IScene> scene) = 0;
        virtual void destroy() = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual ~IRenderer() = default;
    };
}