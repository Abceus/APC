#include "core/game.h"

namespace apc
{
    void IGame::setContext(apc::IContext *context)
    {
        m_context = context;
    }
}