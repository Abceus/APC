#pragma once

#include "core/coord.h"
#include "core/context.h"

namespace apc
{
    class IGame
    {
    public:
        virtual void init() = 0;
        virtual void quit() = 0;
        virtual ~IGame() = default;
        void setContext( IContext* context );
    protected:
        IContext* m_context;
    };
}