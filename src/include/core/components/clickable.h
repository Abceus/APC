#pragma once
#include "core/coord.h"


namespace apc
{
    class IClickable
    {
    public:
        virtual void click( const ICoord& value ) = 0;
    };
}