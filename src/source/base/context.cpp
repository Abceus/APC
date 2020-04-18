#include "base/context.h"
#include "base/gl_renderer.h"

namespace apc
{
    Context& Context::getInstance()
    {
        static Context instance;
        return instance;
    }

    void Context::init()
    {
        m_renderer->init();
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

    void Context::button( const ICoord& value )
    {
        auto currentScene = m_sceneManager->getCurrentScene();
        if(currentScene)
        {
            currentScene->click(value);
        }
        // m_game->button( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                   static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::altButton( const ICoord& value )
    {
        // m_game->altButton( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                      static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::holdedMove( const ICoord& value )
    {
        // m_game->holdedMove( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                       static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::drag( const ICoord& value )
    {
        // m_game->drag( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                 static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::drop( const ICoord& value )
    {
        // m_game->drop( { static_cast<int>( static_cast<float>( value.x ) / static_cast<float>( m_renderer->getWidth() ) * WIDTH ),
        //                 static_cast<int>( static_cast<float>( value.y ) / static_cast<float>( m_renderer->getHeight() ) * HEIGHT ) } );
    }

    void Context::quit()
    {
        m_game->quit();
        m_renderer->destroy();
    }

    void Context::screenSizeChanged( const ICoord& newSize )
    {
        m_renderer->screenChange(newSize.x, newSize.y);
    }

    ISceneManager* Context::getSceneManager()
    {
        return m_sceneManager.get();
    }

    ICoord Context::getScreenSize() const
    {
        return { m_gameConfig.width, m_gameConfig.height };
    }

    ICoord Context::getScaledScreenSize() const
    {
        return coord_cast<ICoord>(static_cast<GLRenderer*>(m_renderer.get())->getScaledScreenSize());
    }

    ICoord Context::getRealScreenSize() const
    {
        return { m_renderer->getWidth(), m_renderer->getHeight() };
    }

    GameConfig Context::getGameConfig() const
    {
        return m_gameConfig;
    }
}