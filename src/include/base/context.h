#pragma once

#include <memory>

#include "core/context.h"
#include "core/renderer.h"
#include "core/game.h"

namespace APC
{
    class Context : public IContext
    {
    public:
        Context(Context const&) = delete;
        void operator=(Context const&) = delete;
        static Context& getInstance();
        template<typename RendererClass, typename GameClass>
        void init(int w, int h);
        void init(int w, int h) override;
        void update( float dt ) override;
        void draw() override;
        void zoom( float delta ) override;
        void button( const Coord& value ) override;
        void altButton( const Coord& value ) override;
        void holdedMove( const Coord& value ) override;
        void drag( const Coord& value ) override;
        void drop( const Coord& value ) override;
    private:
        Context();
        std::unique_ptr<IRenderer> m_renderer;
        std::unique_ptr<IGame> m_game;
    };

    template<typename RendererClass, typename GameClass>
    void Context::init(int w, int h)
    {
        m_renderer = std::make_unique<RendererClass>();
        m_game = std::make_unique<GameClass>();
        init(w, h);
    }
}