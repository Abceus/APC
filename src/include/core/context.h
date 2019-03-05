#pragma once

#include <functional>
#include <sstream>
#include <memory>
#include "core/utility.h"
#include "core/log.h"

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
        template<typename LogType, typename... Args>
        void setLogImpl( Args... args );
        template<typename... Args>
        void log( Args... args );
    private:
        std::unique_ptr<ILog> m_log;
    };
    template<typename LogType, typename... Args>
    void IContext::setLogImpl(Args... args)
    {
        m_log = std::make_unique<LogType>( args... );
    }

    template<typename... Args>
    void IContext::log( Args... args )
    {
        if( m_log )
        {
            std::stringstream ss;
            ( ( ss << args << " " ), ... );
            m_log->print( ss );
        }
    }
}