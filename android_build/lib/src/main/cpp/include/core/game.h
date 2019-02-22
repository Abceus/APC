#pragma once

#include "core/utility.h"

namespace APC
{
    class IGame
    {
    public:
        virtual void init() = 0;
        virtual void update( float dt ) = 0;
        virtual void zoom( float delta ) = 0;
        virtual void button( const Coord& value ) = 0;
        virtual void altButton( const Coord& value ) = 0;
        virtual void holdedMove( const Coord &value ) = 0;
        virtual ~IGame() = default;
    };
}