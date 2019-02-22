#include "base/context.h"

namespace APC
{
    void Context::init(int w, int h)
    {
        m_renderer->init(w, h);
    }

    void Context::update( float dt )
    {

    }

    void Context::draw()
    {
        m_renderer->draw();
    }

    void Context::zoom( float delta )
    {

    }

    void Context::button( const Coord& value )
    {

    }
}