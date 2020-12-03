#pragma once

#include <memory>
#include <sstream>

#include "apc/context.h"
#include "apc/renderer.h"
#include "apc/game.h"
#include "apc/game_config.h"
#include "apc/scene_manager.h"
#include "apc/log.h"
#include "apc/file_loader.h"
#include "apc/resource_manager.h"

namespace apc
{
    class Context
    {
    public:
        Context(Context const&) = delete;
        void operator=(Context const&) = delete;
        static Context& getInstance();

        template<typename RendererClass, typename GameClass>
        void init();

        void init();

        void initRender();
        void deinitRender();

        void update( float dt );
        void draw();
        void zoom( float delta );
        void button( const ICoord& value );
        void altButton( const ICoord& value );
        void holdedMove( const ICoord& value );
        void drag( const ICoord& value );
        void drop( const ICoord& value );
        void quit();
        void screenSizeChanged( const ICoord& newSize );
        SceneManager* getSceneManager();
        ICoord getScreenSize() const;
        ICoord getScaledScreenSize() const;
        ICoord getRealScreenSize() const;
        GameConfig getGameConfig() const;

        template<typename LogType, typename... Args>
        void setLogImpl( Args... args );
        template<typename... Args>
        void log( Args... args );

        template<typename LoaderType, typename... Args>
        void setLoaderImpl( Args... args );

        template<typename ResourceType>
        ResourcePtr<ResourceType> getResource( const std::string &path );
    private:
        Context() = default;
        std::unique_ptr<IRenderer> m_renderer;
        std::unique_ptr<IGame> m_game;
        std::unique_ptr<SceneManager> m_sceneManager;
        GameConfig m_gameConfig;
        std::unique_ptr<ILog> m_log;
        std::unique_ptr<IFileLoader> m_fileLoader;
    };

    template<typename RendererClass, typename GameClass>
    void Context::init()
    {
        m_renderer = std::make_unique<RendererClass>();
        m_game = std::make_unique<GameClass>();
        m_gameConfig = GameClass::getGameConfig();
        init();
    }

    template<typename LogType, typename... Args>
    void Context::setLogImpl(Args... args)
    {
        m_log = std::make_unique<LogType>( args... );
    }
        template<typename... Args>
    void Context::log( Args... args )
    {
        if( m_log )
        {
            std::stringstream ss;
            ( ( ss << args << " " ), ... );
            m_log->print( ss );
        }
    }

    template<typename LoaderType, typename... Args>
    void Context::setLoaderImpl(Args... args)
    {
        m_fileLoader = std::make_unique<LoaderType>( args... );
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType> Context::getResource( const std::string &path )
    {
        if( m_fileLoader )
        {
            static ResourceManager<ResourceType> rm;
            return rm.getResource( path, m_fileLoader.get() );
        }
        return ResourcePtr<ResourceType>();
    }
}