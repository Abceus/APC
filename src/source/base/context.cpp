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
        m_sceneManager = std::make_unique<SceneManager>();
        m_game->setContext(this);
        m_game->init();
    }

    void Context::update( float dt )
    {
        // m_game->update(dt);
        auto currentScene = m_sceneManager->getCurrentScene();
        if(currentScene)
        {
            currentScene->update(dt);
        }
    }

    void Context::draw()
    {
        auto currentScene = m_sceneManager->getCurrentScene();
        if(currentScene)
        {
            m_renderer->draw(currentScene);
        }
    }

    void Context::zoom( float delta )
    {
        // m_game->zoom(delta);
    }

    void Context::button( const Coord& value )
    {
        auto currentScene = m_sceneManager->getCurrentScene();
        if(currentScene)
        {
            currentScene->click(value);
        }
        // m_game->button( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                   static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::altButton( const Coord& value )
    {
        // m_game->altButton( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                      static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::holdedMove( const Coord& value )
    {
        // m_game->holdedMove( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                       static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::drag( const Coord& value )
    {
        // m_game->drag( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                 static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::drop( const Coord& value )
    {
        // m_game->drop( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                 static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::quit()
    {
        m_renderer->destroy();
    }

    void Context::screenSizeChanged( const Coord& newSize )
    {

    }

    ISceneManager* Context::getSceneManager()
    {
        return m_sceneManager.get();
    }

    Coord Context::getScreenSize()
    {
        return { m_renderer->getWidth(), m_renderer->getHeight() };
    }
}