#pragma once

namespace apc
{
    class ILog
    {
    public:
        virtual void print( const std::stringstream &stream ) = 0;
        virtual ~ILog() = default;
    };
}