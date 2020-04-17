#pragma once

#include <memory>

#include "core/context.h"
#include "core/renderer.h"
#include "core/game.h"
#include "core/game_config.h"
#include "base/scene_manager_impl.h"

namespace APC
{
    class Context : public IContext
    {
    public:
        Context(Context const&) = delete;
        void operator=(Context const&) = delete;
        static Context& getInstance();
        template<typename RendererClass, typename GameClass>
        void init();
        void init() override;
        void update( float dt ) override;
        void draw() override;
        void zoom( float delta ) override;
        void button( const Coord& value ) override;
        void altButton( const Coord& value ) override;
        void holdedMove( const Coord& value ) override;
        void drag( const Coord& value ) override;
        void drop( const Coord& value ) override;
        void quit() override;
        void screenSizeChanged( const Coord& newSize ) override;
        ISceneManager* getSceneManager() override;
        Coord getScreenSize() const;
        Coord getRealScreenSize() const;
        GameConfig getGameConfig() const;
    private:
        Context() = default;
        std::unique_ptr<IRenderer> m_renderer;
        std::unique_ptr<IGame> m_game;
        std::unique_ptr<ISceneManager> m_sceneManager;
        GameConfig m_gameConfig;
    };

    template<typename RendererClass, typename GameClass>
    void Context::init()
    {
        m_renderer = std::make_unique<RendererClass>();
        m_game = std::make_unique<GameClass>();
        m_gameConfig = GameClass::getGameConfig();
        init();
    }
}