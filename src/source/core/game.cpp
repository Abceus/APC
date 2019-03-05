#include "core/game.h"

namespace APC
{
    void IGame::setContext(APC::IContext *context)
    {
        m_context = context;
    }
}