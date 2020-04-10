#include "base/sprite.h"

namespace APC
{
    void Drawable::setRenderNode(std::shared_ptr<RenderNode> renderNode)
    {
        m_renderNode = renderNode;
    }

    std::shared_ptr<RenderNode> Drawable::getRenderNode() const
    {
        return m_renderNode;
    }

    bool Drawable::enabled()
    {
        return m_enabled;
    }

    void Drawable::setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }
}