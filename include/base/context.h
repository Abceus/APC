#pragma once

#include <memory>

#include "core/context.h"
#include "core/renderer.h"

namespace APC
{
    class Context : public IContext
    {
    public:
        void init(int w, int h) override;
        void update( float dt ) override;
        void draw() override;
        void zoom( float delta ) override;
        void button( const Coord& value ) override;
    private:
        std::unique_ptr<IRenderer> m_renderer;
    };
}