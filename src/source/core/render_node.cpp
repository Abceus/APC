#include "core/render_node.h"

namespace APC
{
    void RenderNode::setParent(std::shared_ptr<RenderNode> parent)
    {
        m_parent = parent;
    }

    FCoord RenderNode::getPosition() const
    {
        if(m_parent)
        {
            if(m_position)
            {
                return m_parent->getPosition() + m_position->get();
            }
            return m_parent->getPosition();
        }
        if(m_position)
        {
            return m_position->get();
        }
        return FCoord();
    }

    Color RenderNode::getColor() const
    {
        if(m_parent)
        {
            if(m_color)
            {
                return m_parent->getColor() * m_color->get();
            }
            return m_parent->getColor();
        }
        if(m_color)
        {
            return m_color->get();
        }
        return Color();
    }

    glm::mat4 RenderNode::getMatrix() const
    {
        glm::mat4 result(1.0);

        if(m_parent)
        {
            result = m_parent->getMatrix();
        }

        if(m_position)
        {
            result *= m_position->getMatrix();
        }

        if(m_rotation)
        {
            result *= m_rotation->getMatrix();
        }

        if(m_scale)
        {
            result *= m_scale->getMatrix();
        }
        return result;
    }
}