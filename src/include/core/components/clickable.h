#pragma once
#include "core/utility.h"


namespace APC
{
    class IClickable
    {
    public:
        virtual void click( const Coord& value ) = 0;
    };
}