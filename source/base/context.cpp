#include "base/context.h"

namespace APC
{
    Context::Context()
    {

    }

    Context& Context::getInstance()
    {
        static Context instance;
        return instance;
    }

    void Context::init(int w, int h)
    {
        m_renderer->init(w, h);
        m_game->init();
    }

    void Context::update( float dt )
    {
        m_game->update(dt);
    }

    void Context::draw()
    {
        m_renderer->draw();
    }

    void Context::zoom( float delta )
    {
        m_game->zoom(delta);
    }

    void Context::button( const Coord& value )
    {
        m_game->button(value);
    }
}