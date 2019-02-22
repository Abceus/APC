#pragma once

namespace APC
{
    class IRenderer
    {
    public:
        virtual void init(int w, int h) = 0;
        virtual void draw() = 0;
        virtual ~IRenderer() = default;
    };
}