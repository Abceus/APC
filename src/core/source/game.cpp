#include "game.h"

namespace apc
{
    void IGame::setContext(apc::Context *context)
    {
        m_context = context;
    }
}