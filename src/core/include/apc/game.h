#pragma once

#include "apc/coord.h"

namespace apc
{
    class Context;
    
    class IGame
    {
    public:
        virtual void init() = 0;
        virtual void quit() = 0;
        virtual ~IGame() = default;
        void setContext( Context* context );
    protected:
        Context* m_context;
    };
}