#pragma once
#include "core/renderer.h"

namespace APC
{
    class GLRenderer : public IRenderer
    {
        void init(int w, int h) override;
    };
}