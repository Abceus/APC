#pragma once

#include <memory>
#include "core/transform.h"

namespace APC
{
    class RenderNode
    {
    public:
        template<typename T>
        std::shared_ptr<typename std::enable_if<std::is_convertible<T*, ITransform*>::value, T>::type> getTypedTransform();
        void setParent(std::shared_ptr<RenderNode> parent);
        Coord getPosition() const;
        glm::mat4 getMatrix() const;
    private:
        std::shared_ptr<ITransform> m_transform;
        std::shared_ptr<RenderNode> m_parent;
    };

    template<typename T>
    std::shared_ptr<typename std::enable_if<std::is_convertible<T*, ITransform*>::value, T>::type> RenderNode::getTypedTransform()
    {
        auto node = std::dynamic_pointer_cast<T>(m_transform);
        if(node)
        {
            return node;
        }
        m_transform = std::make_shared<T>();
        return std::dynamic_pointer_cast<T>(m_transform);
    }
}