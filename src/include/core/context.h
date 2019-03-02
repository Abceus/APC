#pragma once

#include <functional>
#include <sstream>
#include "core/utility.h"

namespace APC
{
    class IContext
    {
    public:
        virtual void init(int w, int h) = 0;
        virtual void update( float dt ) = 0;
        virtual void draw() = 0;
        virtual void zoom( float delta ) = 0;
        virtual void button( const Coord& value ) = 0;
        virtual void altButton( const Coord& value ) = 0;
        virtual void holdedMove( const Coord& value ) = 0;
        virtual void drag( const Coord& value ) = 0;
        virtual void drop( const Coord& value ) = 0;
        virtual void quit() = 0;
        void setLogFunction( std::function<void(std::stringstream&)>&& logFunction );
        template<typename Arg>
        void log( Arg arg );
        template<typename Arg, typename... Args>
        void log( Arg arg, Args... args );
    private:
        std::function<void(std::stringstream&)> m_logFunction;
    };

    void IContext::setLogFunction( std::function<void(std::stringstream&)>&& logFunction )
    {
        m_logFunction = std::move( logFunction );
    }

    template<typename Arg>
    void IContext::log( Arg arg )
    {
        if( m_logFunction )
        {
            std::stringstream ss;
            ss << arg << std::endl;
            m_logFunction( ss );
        }
    }

    template<typename Arg, typename... Args>
    void IContext::log( Arg arg, Args... args )
    {
        if( m_logFunction )
        {
            std::stringstream ss;
            ss << arg << " ";
            m_logFunction( ss );
            log( args... );
        }
    }
}