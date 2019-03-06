#pragma once

namespace APC
{
    class IRenderer
    {
    public:
        virtual void init(int w, int h) = 0;
        virtual void draw() = 0;
        virtual void destroy() = 0;
        virtual int getWidth() = 0;
        virtual int getHeigth() = 0;
        virtual ~IRenderer() = default;
    };
}