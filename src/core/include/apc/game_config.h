#pragma once

#include <string>

namespace apc
{
    struct GameConfig
    {
        int width = 1024;
        int height = 768;
        std::string gameName = "";
    };
}