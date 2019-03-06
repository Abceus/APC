#include "base/context.h"

namespace APC
{
    const int WIDTH = 800, HEIGHT = 600;

    Context& Context::getInstance()
    {
        static Context instance;
        return instance;
    }

    void Context::init(int w, int h)
    {
        m_renderer->init(w, h);
        m_game->setContext(this);
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
        m_game->button( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
                          static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeigth() ) * HEIGHT ) } );
    }

    void Context::altButton( const Coord& value )
    {
        m_game->altButton( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
                             static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeigth() ) * HEIGHT ) } );
    }

    void Context::holdedMove( const Coord& value )
    {
        m_game->holdedMove( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
                              static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeigth() ) * HEIGHT ) } );
    }

    void Context::drag( const Coord& value )
    {
        m_game->drag( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
                        static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeigth() ) * HEIGHT ) } );
    }

    void Context::drop( const Coord& value )
    {
        m_game->drop( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
                        static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeigth() ) * HEIGHT ) } );
    }

    void Context::quit()
    {
        m_renderer->destroy();
    }
}