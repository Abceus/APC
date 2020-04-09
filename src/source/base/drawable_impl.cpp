#include "base/sprite.h"

namespace APC
{
    // void Drawable::setTransform(std::shared_ptr<ITransform> transform)
    // {
    //     m_transform = transform;
    // }

    // std::shared_ptr<ITransform> Drawable::getTransform() const
    // {
    //     return m_transform;
    // }

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