#include "core/render_node.h"

namespace APC
{
    void RenderNode::setParent(std::shared_ptr<RenderNode> parent)
    {
        m_parent = parent;
    }

    Coord RenderNode::getPosition() const
    {
        if(m_parent)
        {
            if(m_transform)
            {
                return m_parent->getPosition() + m_transform->getPosition();
            }
            return m_parent->getPosition();
        }
        if(m_transform)
        {
            return m_transform->getPosition();
        }
        return {0, 0};
    }

    glm::mat4 RenderNode::getMatrix() const
    {
        if(m_parent)
        {
            if(m_transform)
            {
                return m_parent->getMatrix() * m_transform->getMatrix();
            }
            return m_parent->getMatrix();
        }
        if(m_transform)
        {
            return m_transform->getMatrix();
        }
        return glm::mat4(1.0);
    }
}