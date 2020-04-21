#pragma once

#include <vector>
#include <string>

namespace apc
{
    class IFileLoader
    {
    public:
        virtual std::vector<unsigned char> load( const std::string &path ) const = 0;

        ~IFileLoader() = default;
    };
}
