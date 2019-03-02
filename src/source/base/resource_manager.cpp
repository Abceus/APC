#include "base/resource_manager.h"

namespace APC
{
    ResourcesManager &ResourcesManager::getInstance()
    {
        static ResourcesManager instance;
        return instance;
    }
}