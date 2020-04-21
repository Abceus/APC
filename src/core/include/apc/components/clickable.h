#pragma once
#include "apc/coord.h"


namespace apc
{
    class IClickable
    {
    public:
        virtual void click( const ICoord& value ) = 0;
    };
}