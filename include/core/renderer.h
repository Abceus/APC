#pragma once

namespace APC
{
    class IRenderer
    {
    public:
        virtual void init() = 0;
        virtual void draw() = 0;
    };
}